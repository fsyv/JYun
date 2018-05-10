#include "stdafx.h"
#include "JYunClient.h"

#include "JYunStringBuffer.h"

using namespace std;
using namespace chrono;

JYunClient::JYunClient(bufferevent *bev):
        m_pStringBuffer(nullptr)
{
    m_pBufferevent = bev;
    m_eState = ConnectionState::Confirm;
    m_SessionContactAction = minutes(1);

    m_pStringBuffer = new JYunStringBuffer();
}

JYunClient::~JYunClient()
{
}

void JYunClient::init()
{
    sendConfirmMsg();
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
        m_pStringBuffer->append(buf, ret);
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

    cout << "buffer size = "<<m_pStringBuffer->size() << endl;


    Msg *msg;
    while ((msg = m_pStringBuffer->getMsg()) != nullptr)
        readMsg(msg);

    m_StringBufferMutex.unlock();
}

int JYunClient::sendConfirmMsg()
{
    ConfirmMsg cMsg;
    cMsg.m_iConfirm = rand();

    char *p = new char[sizeof(Msg) + sizeof(ConfirmMsg) + 1];
    memset(p, 0, sizeof(Msg) + sizeof(ConfirmMsg) + 1);

    Msg *msg = (Msg *)p;
    msg->m_MsgHead.m_iMsgLen = sizeof(ConfirmMsg);
    msg->m_MsgHead.m_eMsgType = Ack_Confirm;
    memcpy(msg->m_aMsgData, &cMsg, sizeof(ConfirmMsg));

    int ret = sendMsg(msg);

    delete  []p;
    return ret;
}

int JYunClient::recvConfirmMsg(ConfirmMsg *msg)
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

int JYunClient::sendLoginMsg(std::string username, LoginMsg::LoginType loginType)
{
    LoginMsg cMsg;
    strncpy(cMsg.m_aUsername, username.c_str(), sizeof(cMsg.m_aUsername) - 1);
    cMsg.m_eLogin = loginType;

    Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(LoginMsg) + 1];
    memset(msg, 0, sizeof(Msg) + sizeof(LoginMsg) + 1);

    msg->m_MsgHead.m_iMsgLen = sizeof(LoginMsg);
    msg->m_MsgHead.m_eMsgType = Put_Login;
    memcpy(msg->m_aMsgData, &cMsg, sizeof(LoginMsg));

    return sendMsg(msg);
}

int JYunClient::recvLoginMsg(LoginMsg *msg)
{
    fprintf(stderr, "LoginMsg: %s\n", msg->m_aUsername);
    return sendLoginMsg(msg->m_aUsername, LoginMsg::LoginType::LoginSuccess);
}

int JYunClient::sendMsg(Msg *msg)
{
    msg->m_MsgHead.m_uiBeginFlag = 0xAFAFAFCF;

    return bufferevent_write(m_pBufferevent, (void *)msg, sizeof(Msg) + msg->m_MsgHead.m_iMsgLen);
}

int JYunClient::readMsg(Msg *msg) {

    int ret = 0;
    switch (msg->m_MsgHead.m_eMsgType){
        case Ack_Confirm:
            ret = recvConfirmMsg((ConfirmMsg *)msg->m_aMsgData);
            break;
        case Put_Login:
            ret = recvLoginMsg((LoginMsg *)msg->m_aMsgData);
    }

    return ret;
}

int JYunClient::sendRegisteredMsg(string username, RegisteredMsg::RegisteredType type,
                                  RegisteredMsg::RegisteredResult rusult) {
    return 0;
}

int JYunClient::recvRegisteredMsg(RegisteredMsg *rmsg)
{
    if(!rmsg)
        return 0;

    switch (rmsg->m_eMsgType){
        case RegisteredMsg::CheckUsername:
            break;
        case RegisteredMsg::Registered:
            break;
    }
    return 0;
}

