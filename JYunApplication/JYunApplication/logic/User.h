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
* @brief : 用户实体类
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/8
**/

#include <QtCore>

class User
{
public:
	static User *getInstance();
	static void destroyInstance();

	void setUsername(const QString &username);

	QString &getUsername();
private:
	User();
	virtual ~User();

	QString m_stUsername;

	static User *m_pInstanceUser;
	static QMutex mutex;
};

