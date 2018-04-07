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
* @brief : �ļ�����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/2/21
**/

enum class FileType
{
	Folder = 0x01,		//�ļ���
	Document = 0x02,	//�ĵ�
	Image = 0x04,		//ͼƬ
	Video = 0x08,		//��Ƶ
	Music = 0x10,		//����
	Other = 0x20,		//����
};