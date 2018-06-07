#include "stdafx.h"
#include "JYunTcp.h"

#include "logic/JYunStringBuffer.h"
#include "logic/JYunConfig.h"
#include "logic/JYunTools.h"
#include "messagebox/JYunMessageBox.h"

JYunTcp::JYunTcp(QObject *parent) :
	QTcpSocket(parent),
	m_pBuffer(nullptr)
{
	m_pBuffer = new JYunStringBuffer(2000);
	p_aRecvBuf = new char[2 * SEND_BUF_MAX_SIZE + 1];
	memset(p_aRecvBuf, 0, sizeof(char) * SEND_BUF_MAX_SIZE * 2);

	p_cRearBuf = p_aRecvBuf;
	p_cHeadBuf = p_aRecvBuf;

	m_iMsgLen = 0;

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
		int recvRet = read(p_aRecvBuf, SEND_BUF_MAX_SIZE);

		//读数据错误
		if (recvRet < 0)
		{
			close();
			return QByteArray();
		}

		m_iMsgLen += recvRet;

		if (m_iMsgLen > 2 * RECV_BUF_MAX_SIZE)
		{
			//消息长度大于缓存长度
			exit(-1);
		}

		//接收到总数据已经大于了RECV_BUF_MAX_SIZE
		//为了安全做一定处理
		if (m_iMsgLen > RECV_BUF_MAX_SIZE)
		{
			unsigned char crc[5];
			memset(crc, 0xAF, 4);
			//在收到得buf中查找0xAFAFAFAF标志位
			void *findMove = JYunTools::memstr(p_cHeadBuf, quint64(m_iMsgLen), (void *)crc);

			if (findMove)
			{
				int move = (char *)findMove - p_aRecvBuf;
				m_iMsgLen -= move;
				memcpy(p_aRecvBuf, findMove, m_iMsgLen);
				p_cHeadBuf = p_aRecvBuf;
				p_cRearBuf += m_iMsgLen;
			}
			else
				return QByteArray();
		}

		//如果收到包长度小于结构体长度，暂定为丢弃
		//实际可能会出现拆包情况，收到小于包长度得
		//数据包
		if (m_iMsgLen < sizeof(Msg))
		{
			//指正移到缓存后
			p_cRearBuf += m_iMsgLen;
			return QByteArray();
		}

		p_aRecvBuf[m_iMsgLen] = '\0';

		//暂时没有想到好的解决方法
		//当且仅当发生TCP粘包时会执行这个loop
		//其它情况都无视这个loop
	stickyPackageLoop:

		//翻译buf
		Msg * msg = (Msg *)p_cHeadBuf;

		//校验位是否正确，如果正确则执行下一步
		if (msg->m_MsgHead.m_uiBeginFlag != (unsigned int)0xAFAFAFAF)
		{
			//矫正
			//尽量校正，校正成功则继续
			//否则continue，直到这个数据包被放弃
			unsigned char crc[5];
			memset(crc, 0xAF, 4);
			//在收到得buf中查找0xAFAFAFAF标志位
			void *findMove = JYunTools::memstr(p_cHeadBuf, quint64(m_iMsgLen), (void *)crc);

			if (findMove)
			{
				//找到标志位
				p_cHeadBuf = (char *)findMove;
				m_iMsgLen -= (p_cRearBuf - p_cHeadBuf);

				//重新翻译buf
				msg = (Msg *)p_cHeadBuf;
			}
			else
			{
				//没有找到标志位
				return QByteArray();
			}

		}

		//一个错误得包
		if (msg->m_MsgHead.m_iMsgLen > RECV_BUF_MAX_SIZE || msg->m_MsgHead.m_iMsgLen < 0)
		{
			return QByteArray();
		}

		if (m_iMsgLen < sizeof(Msg) + msg->m_MsgHead.m_iMsgLen)
		{
			//拆包
			p_cRearBuf += m_iMsgLen;
			return QByteArray();
		}

		if (msg->m_MsgHead.m_eMsgType == Get_FileLists)
			byteArray.append(msg->m_aMsgData, msg->m_MsgHead.m_iMsgLen);
		else
		{
			//投递数据包
			recvMsg(msg);
		}
		
		m_iMsgLen -= sizeof(Msg) + msg->m_MsgHead.m_iMsgLen;

		if (m_iMsgLen > 0)
		{
			//黏包
			p_cHeadBuf = p_cHeadBuf + sizeof(Msg) + msg->m_MsgHead.m_iMsgLen;
			goto stickyPackageLoop;
		}

		//一轮结束pRearBuf和pHeadBuf指针重新指向recvBuf
		p_cRearBuf = p_aRecvBuf;
		p_cHeadBuf = p_aRecvBuf;
	}

	//开异步
	connect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));

	return byteArray;
}

int JYunTcp::sendPutFileListMsg(const QString & path, const QString & json)
{
	QString md5 = JYunTools::stringMD5(path);

	//文件列表中可能会有中文。
	int filesLength = strlen(json.toUtf8().data());
	
	PutFileListsMsg *pMsg = (PutFileListsMsg *)new char[sizeof(PutFileListsMsg) + filesLength + 1];
	memset(pMsg, 0, sizeof(PutFileListsMsg) + filesLength + 1);
	strncpy(pMsg->m_aPath, md5.toUtf8().data(), sizeof(pMsg->m_aPath) - 1);
	strncpy(pMsg->m_aData, json.toUtf8().data(), filesLength);

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(PutFileListsMsg) + filesLength + 2];
	memset(msg, 0, sizeof(Msg) + sizeof(PutFileListsMsg) + filesLength + 2);

	msg->m_MsgHead.m_iMsgLen = sizeof(PutFileListsMsg) + filesLength + 1;
	msg->m_MsgHead.m_eMsgType = Put_FileLists;
	memcpy(msg->m_aMsgData, pMsg, msg->m_MsgHead.m_iMsgLen);

	delete pMsg;

	return sendMsg(msg);
}

int JYunTcp::sendNewFolderMsg(const QString & path)
{
	QString md5 = JYunTools::stringMD5(path);

	NewFolderMsg nMsg;
	memset(&nMsg, 0, sizeof(NewFolderMsg));
	strncpy(nMsg.m_aPath, md5.toUtf8().data(), sizeof(nMsg.m_aPath) - 1);

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(NewFolderMsg) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(NewFolderMsg) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(NewFolderMsg);
	msg->m_MsgHead.m_eMsgType = Put_NewFolder;
	memcpy(msg->m_aMsgData, &nMsg, msg->m_MsgHead.m_iMsgLen);

	return sendMsg(msg);
}

int JYunTcp::sendDeleteFolderMsg(const QString & path)
{
	QString md5 = JYunTools::stringMD5(path);

	DeleteFolderMsg dMsg;
	memset(&dMsg, 0, sizeof(DeleteFolderMsg));
	strncpy(dMsg.m_aPath, md5.toUtf8().data(), sizeof(dMsg.m_aPath) - 1);

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(DeleteFolderMsg) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(DeleteFolderMsg) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(DeleteFolderMsg);
	msg->m_MsgHead.m_eMsgType = Put_DeleteFolder;
	memcpy(msg->m_aMsgData, &dMsg, msg->m_MsgHead.m_iMsgLen);

	return sendMsg(msg);
}

int JYunTcp::sendRenameFolderMsg(const QString & oldName, const QString & newName)
{
	RenameFolderMsg rMsg;
	memset(&rMsg, 0, sizeof(RenameFolderMsg));
	QString md5 = JYunTools::stringMD5(oldName);
	strncpy(rMsg.m_aOldName, md5.toUtf8().data(), sizeof(rMsg.m_aOldName) - 1);
	md5 = JYunTools::stringMD5(newName);
	strncpy(rMsg.m_aNewName, md5.toUtf8().data(), sizeof(rMsg.m_aNewName) - 1);

	Msg *msg = (Msg *)new char[sizeof(Msg) + sizeof(RenameFolderMsg) + 1];
	memset(msg, 0, sizeof(Msg) + sizeof(RenameFolderMsg) + 1);

	msg->m_MsgHead.m_iMsgLen = sizeof(RenameFolderMsg);
	msg->m_MsgHead.m_eMsgType = Put_RenameFolder;
	memcpy(msg->m_aMsgData, &rMsg, msg->m_MsgHead.m_iMsgLen);

	return sendMsg(msg);
}

QUrl JYunTcp::url() const
{
	return m_url;
}

int JYunTcp::sendMsg(Msg * msg)
{
	msg->m_MsgHead.m_uiBeginFlag = 0xAFAFAFAF;

	if (state() != ConnectedState)
		connectToServer();

	int ret = write((char *)msg, sizeof(Msg) + msg->m_MsgHead.m_iMsgLen);
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
	int recvRet = read(p_aRecvBuf, SEND_BUF_MAX_SIZE);

	//读数据错误
	if (recvRet < 0)
	{
		close();
		return;
	}

	m_iMsgLen += recvRet;

	if (m_iMsgLen > 2 * RECV_BUF_MAX_SIZE)
	{
		//消息长度大于缓存长度
		exit(-1);
	}

	//接收到总数据已经大于了RECV_BUF_MAX_SIZE
	//为了安全做一定处理
	if (m_iMsgLen > RECV_BUF_MAX_SIZE)
	{
		unsigned char crc[5];
		memset(crc, 0xAF, 4);
		//在收到得buf中查找0xAFAFAFAF标志位
		void *findMove = JYunTools::memstr(p_cHeadBuf, quint64(m_iMsgLen), (void *)crc);

		if (findMove)
		{
			int move = (char *)findMove - p_aRecvBuf;
			m_iMsgLen -= move;
			memcpy(p_aRecvBuf, findMove, m_iMsgLen);
			p_cHeadBuf = p_aRecvBuf;
			p_cRearBuf += m_iMsgLen;
		}
		else
			return;
	}

	//如果收到包长度小于结构体长度，暂定为丢弃
	//实际可能会出现拆包情况，收到小于包长度得
	//数据包
	if (m_iMsgLen < sizeof(Msg))
	{
		//指正移到缓存后
		p_cRearBuf += m_iMsgLen;
		return;
	}

	p_aRecvBuf[m_iMsgLen] = '\0';

	//暂时没有想到好的解决方法
	//当且仅当发生TCP粘包时会执行这个loop
	//其它情况都无视这个loop
stickyPackageLoop:

	//翻译buf
	Msg * msg = (Msg *)p_cHeadBuf;

	//校验位是否正确，如果正确则执行下一步
	if (msg->m_MsgHead.m_uiBeginFlag != (unsigned int)0xAFAFAFAF)
	{
		//矫正
		//尽量校正，校正成功则继续
		//否则continue，直到这个数据包被放弃
		unsigned char crc[5];
		memset(crc, 0xAF, 4);
		//在收到得buf中查找0xAFAFAFAF标志位
		void *findMove = JYunTools::memstr(p_cHeadBuf, quint64(m_iMsgLen), (void *)crc);

		if (findMove)
		{
			//找到标志位
			p_cHeadBuf = (char *)findMove;
			m_iMsgLen -= (p_cRearBuf - p_cHeadBuf);

			//重新翻译buf
			msg = (Msg *)p_cHeadBuf;
		}
		else
		{
			//没有找到标志位
			return;
		}

	}

	//一个错误得包
	if (msg->m_MsgHead.m_iMsgLen > RECV_BUF_MAX_SIZE || msg->m_MsgHead.m_iMsgLen < 0)
	{
		return;
	}

	if (m_iMsgLen < sizeof(Msg) + msg->m_MsgHead.m_iMsgLen)
	{
		//拆包
		p_cRearBuf += m_iMsgLen;
		return;
	}

	//投递数据包
	recvMsg(msg);
	m_iMsgLen -= sizeof(Msg) + msg->m_MsgHead.m_iMsgLen;

	if (m_iMsgLen > 0)
	{
		//黏包
		p_cHeadBuf = p_cHeadBuf + sizeof(Msg) + msg->m_MsgHead.m_iMsgLen;
		goto stickyPackageLoop;
	}

	//一轮结束pRearBuf和pHeadBuf指针重新指向recvBuf
	p_cRearBuf = p_aRecvBuf;
	p_cHeadBuf = p_aRecvBuf;
}

void JYunTcp::displayState(QAbstractSocket::SocketState)
{
	qDebug() << state();
}

void JYunTcp::displayError(QAbstractSocket::SocketError)
{
	JYunMessageBox::prompt(errorString());
}
