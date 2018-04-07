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

#include "../../CommonCode/Msg.h"

class NetworkIO{
public:
    explicit NetworkIO();
    virtual ~NetworkIO();

    int sendConfirmMsg();
    virtual int recvConfirmMsg(ConfirmMsg_t *msg) = 0;

protected:
    virtual int sendMsg(Msg *msg) = 0;
    virtual int readMsg(Msg *msg);
};

#endif //NETWORKIO_H_H