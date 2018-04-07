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
* @brief : 网络通信消息类型
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/2/21
**/

#include <QTcpSocket>

#define SERVER_HOST "119.29.157.226"
#define SERVER_PORT 65530

class BasicNetwork: public QTcpSocket
{
    Q_OBJECT
public:
	explicit BasicNetwork(QObject *parent = nullptr);
	virtual ~BasicNetwork();
protected:
    //纯虚函数，需要在子类中实现
    virtual int sendMsg(Msg *msg) = 0;
    virtual void recvMsg(Msg *msg) = 0;
};

