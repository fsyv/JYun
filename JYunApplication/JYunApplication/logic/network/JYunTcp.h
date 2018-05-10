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

#define SERVER_HOST "119.29.157.226"
#define SERVER_PORT 65530

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

	int sendGetUserHead(const QString &username);
	int recvGetUserHead(GetUserHead *gmsg);

	int sendGetUserHeadMd5Msg(const QString &username);
	int recvGetUserHeadMd5Msg(GetUserHeadMd5 *gmsg);

	QByteArray sendGetFileListsMsg(const QString &path);

	QUrl url() const;

signals:
	void loginMsg(LoginMsg *msg);
	void registeredMsg(RegisteredMsg *msg);
	void getUserHeadMsg(GetUserHead *msg);
	void getUserHeadMd5Msg(GetUserHeadMd5 *msg);
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

	QUrl m_url;
};

