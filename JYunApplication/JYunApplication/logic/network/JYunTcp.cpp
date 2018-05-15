#include "stdafx.h"
#include "JYunTcp.h"

#include "logic/JYunStringBuffer.h"
#include "logic/JYunConfig.h"
#include "logic/JYunTools.h"

JYunTcp::JYunTcp(QObject *parent) :
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
	m_url.setHost(host);
	m_url.setPort(port);

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

int JYunTcp::sendGetUserHeadMd5Msg(const QString & username)
{
	GetUserHeadMd5 gMsg;
	strncpy(gMsg.m_aUsername, username.toUtf8().data(), sizeof(gMsg.m_aUsername) - 1);

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(GetUserHeadMd5) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(GetUserHeadMd5) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(GetUserHeadMd5);
	msg->m_MsgHead.m_eMsgType = Get_HeadMd5;
	memcpy(msg->m_aMsgData, &gMsg, sizeof(GetUserHeadMd5));

	return sendMsg(msg);
}

int JYunTcp::recvGetUserHeadMd5Msg(GetUserHeadMd5 * gmsg)
{
	GetUserHeadMd5 *msg = new GetUserHeadMd5;
	memcpy(msg, gmsg, sizeof(GetUserHeadMd5));
	emit getUserHeadMd5Msg(msg);

	return 0;
}

int JYunTcp::sendModifypassMsg(const QString & username, const QString & userpass, const QString head_md5)
{
	ModifypassMsg mMsg;
	strncpy(mMsg.m_aUsername, username.toUtf8().data(), sizeof(mMsg.m_aUsername) - 1);
	strncpy(mMsg.m_aPassword, userpass.toUtf8().data(), sizeof(mMsg.m_aPassword) - 1);
	strncpy(mMsg.m_aMd5, head_md5.toUtf8().data(), sizeof(mMsg.m_aMd5) - 1);

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(ModifypassMsg) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(ModifypassMsg) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(ModifypassMsg);
	msg->m_MsgHead.m_eMsgType = Put_Modifypass;
	memcpy(msg->m_aMsgData, &mMsg, sizeof(ModifypassMsg));

	return sendMsg(msg);
}

int JYunTcp::recvModifypassMsg(ModifypassMsg * gmsg)
{
	ModifypassMsg *msg = new ModifypassMsg;
	memcpy(msg, gmsg, sizeof(ModifypassMsg));
	emit modifypassMsg(msg);

	return 0;
}

QByteArray JYunTcp::sendGetFileListsMsg(const QString & path)
{
	//关异步
	disconnect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));

	QString path_upper = path.toUpper();

	QString md5 = JYunTools::stringMD5(path_upper);

	Msg *msg = (Msg *)new char[sizeof(Msg) + md5.size() + 1];
	memset(msg, 0, sizeof(Msg) + md5.size() + 1);

	msg->m_MsgHead.m_iMsgLen = md5.size();
	msg->m_MsgHead.m_eMsgType = Get_FileLists;
	memcpy(msg->m_aMsgData, md5.toUtf8().data(), msg->m_MsgHead.m_iMsgLen);

	sendMsg(msg);
	QByteArray byteArray;
	if (waitForReadyRead(1000))
	{
		byteArray = readAll();
		m_pBuffer->append(byteArray.data(), byteArray.size());

		Msg *msg = nullptr;

		while ((msg = m_pBuffer->getMsg()) != nullptr)
		{
			if (msg->m_MsgHead.m_eMsgType != Get_FileLists)
			{
				recvMsg(msg);
				delete msg;
				msg = nullptr;
			}
			else
				break;
		}

		byteArray.clear();
		byteArray = QByteArray(msg->m_aMsgData);
	}

	//开异步
	connect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));

	return byteArray;
}

int JYunTcp::sendPutFileListMsg(const QString & path, const QString & json)
{
	QString path_upper = path.toUpper();

	QString md5 = JYunTools::stringMD5(path_upper);

	PutFileListsMsg *pMsg = (PutFileListsMsg *)new char[sizeof(PutFileListsMsg) + json.size() + 1];
	strncpy(pMsg->m_aPath, md5.toUtf8().data(), sizeof(pMsg->m_aPath) - 1);
	strncpy(pMsg->m_aData, json.toUtf8().data(), json.length());

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(PutFileListsMsg) + json.size() + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(PutFileListsMsg) + json.size() + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(PutFileListsMsg) + json.size();
	msg->m_MsgHead.m_eMsgType = Put_FileLists;
	memcpy(msg->m_aMsgData, &pMsg, msg->m_MsgHead.m_iMsgLen);

	delete pMsg;

	return sendMsg(msg);
}

QUrl JYunTcp::url() const
{
	return m_url;
}

int JYunTcp::sendMsg(Msg * msg)
{
	msg->m_MsgHead.m_uiBeginFlag = 0xAFAFAFCF;

	if (state() != ConnectedState)
		connectToServer();

	int ret = write((char *)msg, sizeof(Msg) + msg->m_MsgHead.m_iMsgLen);

	waitForBytesWritten(1);

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
	case Put_Registered:
		recvRegisteredMsg((RegisteredMsg *)msg->m_aMsgData);
	case Get_HeadMd5:
		recvGetUserHeadMd5Msg((GetUserHeadMd5 *)msg->m_aMsgData);
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
