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
* @brief : 本地数据库
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

	//从本地数据库获取用户列表
	QStringList getUserLists();
	//从本地数据库获取是否自动登录
	bool isAutoLogin();
private:
	QSqlDatabase db;
};

