#pragma once
#pragma execution_character_set("utf-8")

/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : Tcp
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/04/05
**/

//接收Buf最大缓存
#define RECV_BUF_MAX_SIZE 64 * 1024
//发送Buf最大缓存
#define SEND_BUF_MAX_SIZE RECV_BUF_MAX_SIZE

class JYunStringBuffer;

class JYunTcp : public QTcpSocket
{
    Q_OBJECT
public:
	explicit JYunTcp(QObject *parent = nullptr);
	~JYunTcp();

	bool connectToServer();

	int sendConfirmMsg(int confirm);
	int recvConfirmMsg(ConfirmMsg *msg);

	int sendLoginMsg(const QString username, const QString password);
	int recvLoginMsg(LoginMsg *msg);

	int sendRegisteredMsg(const RegisteredMsg &rmsg);
	int recvRegisteredMsg(RegisteredMsg *rmsg);

	int sendGetUserHeadMd5Msg(const QString &username);
	int recvGetUserHeadMd5Msg(GetUserHeadMd5 *gmsg);

	int sendModifypassMsg(const QString &username, const QString &userpass, const QString head_md5);
	int recvModifypassMsg(ModifypassMsg *mmsg);

	QByteArray sendGetFileListsMsg(const QString &path);

	int sendPutFileListMsg(const QString &path, const QString &json);

	int sendNewFolderMsg(const QString &path);
	int sendDeleteFolderMsg(const QString &path);
	int sendRenameFolderMsg(const QString &oldName, const QString &newName);

	QUrl url() const;

signals:
	void loginMsg(LoginMsg *msg);
	void registeredMsg(RegisteredMsg *msg);
	void getUserHeadMd5Msg(GetUserHeadMd5 *msg);
	void modifypassMsg(ModifypassMsg *gmsg);
	void getFileListsMsg(QByteArray &bytearray);

protected:

	int sendMsg(Msg *msg);
	void recvMsg(Msg *msg);

	void dumpMessage();

protected slots:
	void readMessage();
	void displayState(QAbstractSocket::SocketState);
	void displayError(QAbstractSocket::SocketError);

private:
	JYunStringBuffer *m_pBuffer;

	char *p_aRecvBuf;
	char *p_cRearBuf;
	char *p_cHeadBuf;
	int m_iMsgLen;

	QUrl m_url;
};

