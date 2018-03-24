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

//消息类型
typedef enum _MsgType {
	Ack_OK = 0,         //确定成功
	Ack_Error,          //确定错误
	Get_Download,		//下载
	Put_Upload			//上传
}MsgType;

