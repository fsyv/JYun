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

class FileObject;

class Database
{
public:
	Database();
	~Database();

	//设置登录时候用户配置
	void setLoginConfig(QString username, bool rememberpass, bool autologin);
	//保存用户名密码
	void setUsernamepass(QString username, QString userpass);

	//从本地数据库获取用户列表
	QStringList getUserLists();
	//从本地数据库获取是否自动登录
	bool isAutoLogin(QString username);
	//从本地数据库获取是否记住密码
	bool isRememberPass(QString username);
	//从本地数据库通过帐号获取密码
	QString getPassByUsername(QString username);
	//保存文件列表到本地
	void saveFilesToLocal(const QString &path, const QList<FileObject *> &files);
	void saveFilesToLocal(const QString &path, const QByteArray &bytearray);
	//从本地缓存获取文件列表
	QByteArray getFilesFromLocal(const QString &path);
	//文件缓存是否有效
	bool isLocalCacheValid(const QString &path);

	void setDownloadPath(const QString &path);
	QString getDownloadPath();
private:
	QSqlDatabase db;
};

