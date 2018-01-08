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
* @brief : �������ݿ�
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/8
**/

#include <QSqlDatabase>

class Database
{
public:
	Database();
	~Database();

	//�ӱ������ݿ��ȡ�û��б�
	QStringList getUserLists();
	//�ӱ������ݿ��ȡ�Ƿ��Զ���¼
	bool isAutoLogin();
private:
	QSqlDatabase db;
};

