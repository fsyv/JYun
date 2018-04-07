#include "stdafx.h"
#include "JYunClient.h"

#include "../../CommonCode/JYunStringBuffer.h"

using namespace std;
using namespace chrono;

JYunClient::JYunClient(bufferevent *bev):
        m_pStringBuffer(nullptr)
{
    m_pBufferevent = bev;
    m_eState = ConnectionState::Confirm;
    m_SessionContactAction = minutes(1);
}

JYunClient::~JYunClient()
{
}

void JYunClient::init()
{
    sendConfirmMsg();
}

int JYunClient::recvConfirmMsg(ConfirmMsg_t *msg)
{
    fprintf(stderr, "ConfirmMsg: %d\n", msg->m_iConfirm);

    if (m_eState == ConnectionState::Confirm)
        m_SessionContactAction = minutes(15);
    else
    {
        //异常
    }
    return 0;
}


int JYunClient::sendMsg(Msg *msg)
{
    msg->m_MsgHead.m_uiBeginFlag = 0xAFAFAFCF;

    return bufferevent_write(m_pBufferevent, (void *)msg, sizeof(Msg) + msg->m_MsgHead.m_iMsgLen);
}

void JYunClient::close()
{
    //客户端主动关闭了close请求
    m_eState = ConnectionState::Closing;
    m_eState = ConnectionState::Closed;
}

void JYunClient::readMsgBuffer()
{
    //同步
//    char buf[512];
//    int ret = 0;
//    while ((ret = bufferevent_read(m_pBufferevent, buf, 512)) > 0)
//    {
//        buf[ret] = 0;
//        m_pStringBuffer << buf;
//    }

    //todo

    //printf("%s\n", m_stringstream.str().c_str());
    //异步
    char buf[512];
    int ret = 0;
    while ((ret = bufferevent_read(m_pBufferevent, buf, 512)) > 0)
    {
        buf[ret] = 0;
        m_pStringBuffer->append(buf);
    }
}

void JYunClient::checkState()
{
    //比较是否超时，如果超时设置state为false
}

JYunClient::ConnectionState JYunClient::state()
{
    checkState();
    return m_eState;
}

void JYunClient::refreshContactTime()
{
    m_LastContactTimeStamps = system_clock::now();
}

void JYunClient::run()
{
    m_StringBufferMutex.lock();

    cout << m_pStringBuffer->size();


    Msg *msg;
    while ((msg = m_pStringBuffer->getMsg()) != nullptr)
        readMsg(msg);

    m_StringBufferMutex.unlock();
}