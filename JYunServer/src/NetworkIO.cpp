#include "stdafx.h"
#include "MsgType.h"
#include "NetworkIO.h"

NetworkIO::NetworkIO()
{

}

NetworkIO::~NetworkIO()
{

}



int NetworkIO::sendConfirmMsg()
{
    ConfirmMsg_t cMsg;
    cMsg.m_iConfirm = rand();

    char *p = new char[sizeof(Msg) + sizeof(ConfirmMsg_t) + 1];
    memset(p, 0, sizeof(Msg) + sizeof(ConfirmMsg_t) + 1);

    Msg *msg = (Msg *)p;
    msg->m_iMsgLen = sizeof(ConfirmMsg_t);
    msg->m_eMsgType = Ack_Confirm;
    memcpy(msg->m_aMsgData, &cMsg, sizeof(ConfirmMsg_t));

    int ret = sendMsg(msg);

    delete  []p;
    return ret;
}

int NetworkIO::readMsg(Msg *msg) {
    return 0;
}
