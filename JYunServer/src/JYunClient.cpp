#include "stdafx.h"
#include "JYunClient.h"

using namespace std;
using namespace chrono;

JYunClient::JYunClient(bufferevent *bev)
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

int JYunClient::sendMsg(Msg *msg)
{
    msg->m_uiBeginFlag = 0xAFAFAFCF;
    msg->m_uiEndFlag = 0xCFCFCFAF;

    return bufferevent_write(m_pBufferevent, (void *)msg, sizeof(Msg) + msg->m_iMsgLen);
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
    char buf[512];
    int ret = 0;
    while ((ret = bufferevent_read(m_pBufferevent, buf, 512)) > 0)
    {
        buf[ret] = 0;
        printf("%ssize = %d\n", buf, ret);
        m_stringstream << buf;
    }

    //printf("%s\n", m_stringstream.str().c_str());
    //异步
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
