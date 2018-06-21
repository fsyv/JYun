#include "stdafx.h"
#include "TransferProcess.h"

using namespace std;

TransferProcess::TransferProcess(bufferevent *bev) :
    m_pBufferevent(bev)
{

}

TransferProcess::~TransferProcess()
{
    close();

    bufferevent_free(m_pBufferevent);
}

bool TransferProcess::init()
{
    return false;
}

void TransferProcess::close()
{

}

void TransferProcess::readMsgBuffer()
{
    FileProcessMsg *msg = NULL;

    //接收缓存
    char *recvBuf = (char *)malloc((2 * RECV_BUF_MAX_SIZE + 1) * sizeof(char));
    memset(recvBuf, 0, 2 * RECV_BUF_MAX_SIZE * sizeof(char));

    //recvBuf尾部指针，用于接收数据
    char *pRearBuf = recvBuf;
    //recvBuf头部指针，用于传递数据
    char *pHeadBuf = recvBuf;
    //实际接收到得字节数量
    int recvRet = 0;
    //消息长度
    int msgLen = 0;
    int msgStructLen = sizeof(FileProcessMsg);

    //发送的数据包不会超过RECV_BUF_MAX_SIZE
    //如果超过RECV_BUF_MAX_SIZE可能出现了TCP
    //粘包现象
    while(recvRet = bufferevent_read(m_pBufferevent, pRearBuf, RECV_BUF_MAX_SIZE))
    {
        //读数据错误
        if(recvRet < 0)
        {
            break;
        }

        msgLen += recvRet;

        if (msgLen > 2 * RECV_BUF_MAX_SIZE)
        {
            //消息长度大于缓存长度
            exit(-1);
        }

        //接收到总数据已经大于了RECV_BUF_MAX_SIZE
        //为了安全做一定处理
        if(msgLen > RECV_BUF_MAX_SIZE)
        {
            unsigned char crc[5];
            memset(crc, 0xAF, 4);
            //在收到得buf中查找0xAFAFAFAF标志位
            //void *findMove = memstr(pHeadBuf, (memlen_t)msgLen, (void *)crc);
            void *findMove = nullptr;

            if(findMove)
            {
                int move = (char *)findMove - recvBuf;
                msgLen -= move;
                memcpy(recvBuf, findMove, msgLen);
                pHeadBuf = recvBuf;
                pRearBuf += msgLen;
            }
            else
            {
                break;
            }
        }

        //如果收到包长度小于结构体长度，暂定为丢弃
        //实际可能会出现拆包情况，收到小于包长度得
        //数据包
        if(msgLen < msgStructLen)
        {
            //指正移到缓存后
            pRearBuf += msgLen;
            continue;
        }

        recvBuf[msgLen] = '\0';

        //暂时没有想到好的解决方法
        //当且仅当发生TCP粘包时会执行这个loop
        //其它情况都无视这个loop
        stickyPackageLoop:

        //翻译buf
        msg = (FileProcessMsg *)pHeadBuf;

        //校验位是否正确，如果正确则执行下一步
        if(msg->m_uiBeginFlag != (unsigned int)0xBFBFBFBF)
        {
            //矫正
            //尽量校正，校正成功则继续
            //否则continue，直到这个数据包被放弃
            unsigned char crc[5];
            memset(crc, 0xBF, 4);
            //在收到得buf中查找0xAFAFAFAF标志位
            //void *findMove = memstr(pHeadBuf, msgLen, (void *)crc);
            void *findMove = nullptr;

            if(findMove)
            {
                //找到标志位
                pHeadBuf = (char *)findMove;
                msgLen -= (pRearBuf - pHeadBuf);

                //重新翻译buf
                msg = (FileProcessMsg *)pHeadBuf;
            }
            else
            {
                //没有找到标志位
                continue;
            }
        }

        //一个错误得包
        if(msg->m_iSize > RECV_BUF_MAX_SIZE - msgStructLen || msg->m_iSize < 0)
        {
            break;
        }

        if(msgLen < msgStructLen + msg->m_iSize)
        {
            //拆包
            pRearBuf += msgLen;
            continue;
        }

        //投递数据包
        recvFileProcessMsg(msg);
        msgLen -= msgStructLen + msg->m_iSize;

        if(msgLen > 0)
        {
            //黏包
            pHeadBuf = pHeadBuf + msgStructLen + msg->m_iSize;
            goto stickyPackageLoop;
        }

        //一轮结束pRearBuf和pHeadBuf指针重新指向recvBuf
        pRearBuf = recvBuf;
        pHeadBuf = recvBuf;
    }

    free(recvBuf);
}

int TransferProcess::upload(string filename, uint64_t offset, int size, char *data)
{
    ofstream file(filename, ios_base::binary);

    uint64_t begin = file.tellp();

    if(begin != offset)
        file.seekp(offset, ios::beg);

    file.write(data, size);

    return sendFilePrecessMsg(FileProcessMsg::Upload, filename, time(nullptr), file.tellp());
}

int TransferProcess::download(string filename, uint64_t offset, int size)
{
    ifstream file(filename, ios_base::binary);

    char *data = new char[size + 1];
    memset(data, 0, size + 1);

    file.seekg(offset, ios::beg);
    file.read(data, size);
    uint64_t count = file.gcount();

    return sendFilePrecessMsg(FileProcessMsg::Download, filename, time(nullptr), offset, count, data);
}

int TransferProcess::recvFileProcessMsg(FileProcessMsg *fMsg)
{
    switch (fMsg->m_eTaskType){
        case FileProcessMsg::Upload:
            upload(fMsg->m_aFileName, fMsg->m_ullOffset, fMsg->m_iSize, fMsg->m_aData);
            break;
        case FileProcessMsg::Download:
            download(fMsg->m_aFileName, fMsg->m_ullOffset, fMsg->m_iSize);
            break;
    }

    return 0;
}

int TransferProcess::sendFilePrecessMsg(FileProcessMsg::FileProcessType type, string filename, uint32_t  timestamp, uint64_t offset,
                                        int size, char *data)
{
    FileProcessMsg *fMsg = (FileProcessMsg *)new char[sizeof(FileProcessMsg) + size + 1];;
    memset(fMsg, 0, sizeof(FileProcessMsg) + size + 1);
    fMsg->m_uiBeginFlag = 0xBFBFBFBF;
    fMsg->m_eTaskType = type;
    strncpy(fMsg->m_aFileName, filename.c_str(), sizeof(fMsg->m_aFileName) - 1);
    fMsg->m_uiTimestamp = timestamp;
    fMsg->m_ullOffset = offset;
    fMsg->m_iSize = size;
    memcpy(fMsg->m_aData, data, fMsg->m_iSize);

    int ret = bufferevent_write(m_pBufferevent, (void *)fMsg, sizeof(FileProcessMsg) + fMsg->m_iSize);

    delete fMsg;

    return ret;
}

