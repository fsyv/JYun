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
* @brief : 文件传输类（可用FTP代替）
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/6/18
**/

#include <QTcpSocket>

class FileProcess : QObject
{
	Q_OBJECT
public:
	FileProcess();
	~FileProcess();

	void connect();
	void disconnect();
	void request();
	void setPort(quint16 port);

protected slots:
	void readMessage();
	void displayState(QAbstractSocket::SocketState);
	void displayError(QAbstractSocket::SocketError);

private:
	quint16 m_usPort;
	QTcpSocket *m_pSocket;
};

