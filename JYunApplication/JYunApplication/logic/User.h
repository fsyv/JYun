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
	User();
	virtual ~User();

	void setUsername(const QString &username);

	QString &getUsername();

	void setDownloadPath(const QString &path);
	QString &getDownloadPath();

private:
	QString m_stUsername;
	QString m_strDownloadPath;
};

