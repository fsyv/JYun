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
* @brief : ����ͨ����Ϣ����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/2/21
**/

//��Ϣ����
typedef enum _MsgType {
	Ack_OK = 0,         //ȷ���ɹ�
	Ack_Error,          //ȷ������
	Get_Download,		//����
	Put_Upload			//�ϴ�
}MsgType;

