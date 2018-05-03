#include "stdafx.h"
#include "JYunTcp.h"

#include "logic/JYunStringBuffer.h"
#include "logic/JYunConfig.h"

JYunTcp::JYunTcp(QObject *parent):
	QTcpSocket(parent),
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

bool JYunTcp::connectToServer()
{
	JYunConfig *sysconfig = GlobalParameter::getInstance()->getConfig();
	QFile file(QDir::currentPath() + "/" + sysconfig->getConfigPath("network"));

	if (!file.open(QIODevice::ReadOnly))
		return false;

	QJsonDocument document = QJsonDocument::fromJson(file.readAll());

	file.close();

	if (document.isNull())
		return false;

	QString host = document.object().value("host").toString();
	quint16 port = document.object().value("port").toInt();

	connectToHost(host, port);
	return waitForConnected(1000);
}

int JYunTcp::sendConfirmMsg(int confirm)
{
	ConfirmMsg cMsg;
	cMsg.m_iConfirm = confirm - 1;

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(ConfirmMsg) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(ConfirmMsg) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(ConfirmMsg);
	msg->m_MsgHead.m_eMsgType = Ack_Confirm;
	memcpy(msg->m_aMsgData, &cMsg, sizeof(ConfirmMsg));

	return sendMsg(msg);
}

int JYunTcp::recvConfirmMsg(ConfirmMsg * msg)
{
	return sendConfirmMsg(msg->m_iConfirm);
}

int JYunTcp::sendLoginMsg(const QString username, const QString password)
{
	LoginMsg cMsg;
	strncpy(cMsg.m_aUsername, username.toUtf8().data(), sizeof(cMsg.m_aUsername) - 1);
	strncpy(cMsg.m_aPassword, password.toUtf8().data(), sizeof(cMsg.m_aPassword) - 1);
	cMsg.m_eLogin = LoginMsg::LoginType::NotLogin;

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(LoginMsg) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(LoginMsg) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(LoginMsg);
	msg->m_MsgHead.m_eMsgType = Put_Login;
	memcpy(msg->m_aMsgData, &cMsg, sizeof(LoginMsg));

	return sendMsg(msg);
}

int JYunTcp::recvLoginMsg(LoginMsg * msg)
{
	LoginMsg *login = new LoginMsg;
	memcpy(login, msg, sizeof(LoginMsg));
	emit loginMsg(login);
	return 0;
}

int JYunTcp::sendRegisteredMsg(const RegisteredMsg &rmsg)
{
	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(RegisteredMsg) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(RegisteredMsg) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(RegisteredMsg);
	msg->m_MsgHead.m_eMsgType = Put_Registered;
	memcpy(msg->m_aMsgData, &rmsg, sizeof(RegisteredMsg));

	return sendMsg(msg);
}

int JYunTcp::recvRegisteredMsg(RegisteredMsg * rmsg)
{
	RegisteredMsg *msg = new RegisteredMsg;
	memcpy(msg, rmsg, sizeof(RegisteredMsg));
	emit registeredMsg(msg);

	return 0;
}

int JYunTcp::sendGetUserHead(const QString & username)
{
	GetUserHead gMsg;
	strncpy(gMsg.m_aUsername, username.toUtf8().data(), sizeof(gMsg.m_aUsername) - 1);

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(GetUserHead) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(GetUserHead) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(GetUserHead);
	msg->m_MsgHead.m_eMsgType = Get_UserHead;
	memcpy(msg->m_aMsgData, &gMsg, sizeof(GetUserHead));

	return sendMsg(msg);
}

int JYunTcp::recvGetUserHead(GetUserHead * gmsg)
{
	GetUserHead *msg = new GetUserHead;
	memcpy(msg, gmsg, sizeof(GetUserHead));
	emit getUserHeadMsg(gmsg);

	return 0;
}

int JYunTcp::sendGetUserHeadMd5Msg(const QString & username)
{
	GetUserHeadMd5 gMsg;
	strncpy(gMsg.m_aUsername, username.toUtf8().data(), sizeof(gMsg.m_aUsername) - 1);

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(GetUserHeadMd5) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(GetUserHeadMd5) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(GetUserHeadMd5);
	msg->m_MsgHead.m_eMsgType = Get_HeadMd5;
	memcpy(msg->m_aMsgData, &gMsg, sizeof(GetUserHeadMd5));

	return 0;
}

int JYunTcp::recvGetUserHeadMd5Msg(GetUserHeadMd5 * gmsg)
{
	GetUserHeadMd5 *msg = new GetUserHeadMd5;
	memcpy(msg, gmsg, sizeof(GetUserHeadMd5));
	emit getUserHeadMd5Msg(gmsg);

	return 0;
}

int JYunTcp::sendMsg(Msg * msg)
{
	msg->m_MsgHead.m_uiBeginFlag = 0xAFAFAFCF;

	int ret = write((char *)msg, sizeof(Msg) + msg->m_MsgHead.m_iMsgLen);

	waitForBytesWritten(1);

	delete msg;

	return ret;
}

void JYunTcp::recvMsg(Msg * msg)
{
	switch (msg->m_MsgHead.m_eMsgType) {
	case Ack_Confirm:
		recvConfirmMsg((ConfirmMsg *)msg->m_aMsgData);
		break;
	case Put_Login:
		recvLoginMsg((LoginMsg *)msg->m_aMsgData);
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
