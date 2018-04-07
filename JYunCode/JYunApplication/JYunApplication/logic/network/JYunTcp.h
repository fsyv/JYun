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

#include "basic\BasicNetwork.h"

class JYunStringBuffer;

class JYunTcp : public BasicNetwork
{
    Q_OBJECT
public:
	explicit JYunTcp(QObject *parent = nullptr);
	~JYunTcp();

	void connectToServer();

protected:
	int sendConfirmMsg(int confirm);
	int recvConfirmMsg(ConfirmMsg_t *msg);

	int sendMsg(Msg *msg) override;
	void recvMsg(Msg *msg) override;

	void dumpMessage();

protected slots:
	void readMessage();
	void displayState(QAbstractSocket::SocketState);
	void displayError(QAbstractSocket::SocketError);

private:
	JYunStringBuffer *m_pBuffer;
};

