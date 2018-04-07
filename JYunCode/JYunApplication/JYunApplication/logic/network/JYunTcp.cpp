#include "stdafx.h"
#include "JYunTcp.h"

#include "../../CommonCode/JYunStringBuffer.h"

JYunTcp::JYunTcp(QObject *parent):
	BasicNetwork(parent),
	m_pBuffer(nullptr)
{
	m_pBuffer = new JYunStringBuffer(2000);

	connect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));
	connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(displayState(QAbstractSocket::SocketState)));
	connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

	connectToServer();
}


JYunTcp::~JYunTcp()
{
}

void JYunTcp::connectToServer()
{
	connectToHost(SERVER_HOST, SERVER_PORT);
	 waitForConnected();
}

int JYunTcp::sendConfirmMsg(int confirm)
{
	ConfirmMsg_t cMsg;
	cMsg.m_iConfirm = confirm - 1;


	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(ConfirmMsg_t) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(ConfirmMsg_t) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(ConfirmMsg_t);
	msg->m_MsgHead.m_eMsgType = Ack_Confirm;
	memcpy(msg->m_aMsgData, &cMsg, sizeof(ConfirmMsg_t));

	return sendMsg(msg);
}

int JYunTcp::recvConfirmMsg(ConfirmMsg_t * msg)
{
	return sendConfirmMsg(msg->m_iConfirm);
}

int JYunTcp::sendMsg(Msg * msg)
{
	msg->m_MsgHead.m_uiBeginFlag = 0xAFAFAFCF;

	int ret = write((char *)msg, sizeof(Msg) + msg->m_MsgHead.m_iMsgLen);

	waitForBytesWritten();

	delete msg;

	return ret;
}

void JYunTcp::recvMsg(Msg * msg)
{
	switch (msg->m_MsgHead.m_eMsgType) {
	case Ack_Confirm:
		recvConfirmMsg((ConfirmMsg_t *)msg->m_aMsgData);
		break;
	default:
		break;
	}
}

void JYunTcp::dumpMessage()
{
	Msg *msg = nullptr;

	while ((msg = m_pBuffer->getMsg()) != nullptr)
	{
		recvMsg(msg);
		delete msg;
		msg = nullptr;
	}
}

void JYunTcp::readMessage()
{
	QByteArray byteArray = readAll();
	m_pBuffer->append(byteArray.data(), byteArray.size());

	dumpMessage();
}

void JYunTcp::displayState(QAbstractSocket::SocketState)
{
	qDebug() << state();
}

void JYunTcp::displayError(QAbstractSocket::SocketError)
{
	qDebug() << errorString();
}
