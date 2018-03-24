#ifndef NETWORKIO_H_H
#define NETWORKIO_H_H

/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 预编译头
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/3/17
**/

#include "MsgType.h"

typedef struct _Msg{
    unsigned int m_uiBeginFlag;     //开始校验位 0xAFAFAFCF
    MsgType m_eMsgType;             //消息类型
    int m_iMsgLen;                  //消息长度
    unsigned int m_uiEndFlag;       //结束校验位 0xCFCFCFAF
    char m_aMsgData[0];             //消息内容
} Msg, *pMsg;

class NetworkIO{
public:
    explicit NetworkIO();
    virtual ~NetworkIO();

    int sendConfirmMsg();

protected:
    virtual int sendMsg(Msg *msg) = 0;
    virtual int readMsg(Msg *msg);
};

#endif //NETWORKIO_H_H