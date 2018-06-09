#include "stdafx.h"
#include "Database.h"

#include "logic\JYunTools.h"
#include "logic\file\FileObject.h"
#include "logic\file\File.h"

Database::Database()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("data");

	if (!db.open())
		qDebug() << db.lastError();
}


Database::~Database()
{
	db.close();
}

/***************************************************
*置登录时候用户配置
****************************************************
*/
void Database::setLoginConfig(QString username, bool rememberpass, bool autologin)
{
	QSqlQuery query(db);

	query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'(%2, %3, %4);")\
		.arg("TABLE_LOGIN_CONFIG")
		.arg("username VARCHAR(16) PRIMARY KEY NOT NULL")
		.arg("remember_pass BOOLEAN")
		.arg("auto_login BOOLEAN")
	);

	//存在则更新，不存在则插入
	query.exec(QString("REPLACE INTO TABLE_LOGIN_CONFIG(username, remember_pass, auto_login) VALUES('%1', '%2', '%3');")
		.arg(username)
		.arg(rememberpass)
		.arg(autologin)
	);

	db.commit();
}

/***************************************************
*保存用户名密码
****************************************************
*/
void Database::setUsernamepass(QString username, QString userpass)
{
	QSqlQuery query(db);

	query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'(%2, %3);")\
		.arg("TABLE_USER_PASS")
		.arg("username VARCHAR(16) PRIMARY KEY NOT NULL")
		.arg("userpass VARCHAR(32)")
	);

	//存在则更新，不存在则插入
	query.exec(QString("REPLACE INTO TABLE_USER_PASS(username, userpass) VALUES('%1','%2');")
		.arg(username)
		.arg(userpass)
	);

	db.commit();
}

/***************************************************
*从本地数据库获取用户列表
****************************************************
*/
QStringList Database::getUserLists()
{
	QSqlQuery query(db);
	QString str("SELECT username FROM TABLE_USER_PASS;");
	QStringList users;

	if(!query.exec(str))
		return users;

	while (query.next())
	{
		users.push_back(
			query.value("username").toString()
		);
	}

	return users;
}

/***************************************************
*从本地数据库获取是否自动登录
****************************************************
*/
bool Database::isAutoLogin(QString username)
{
	QSqlQuery query(db);
	QString str(QString("SELECT auto_login FROM TABLE_LOGIN_CONFIG WHERE username='%1';")
		.arg(username)
	);

	if (!query.exec(str))
		return false;

	query.first();

	return query.value("auto_login").toBool();
}

/***************************************************
*从本地数据库获取是否记住密码
****************************************************
*/
bool Database::isRememberPass(QString username)
{
	QSqlQuery query(db);
	QString str(QString("SELECT remember_pass FROM TABLE_LOGIN_CONFIG WHERE username='%1';")
		.arg(username)
	);

	if (!query.exec(str))
		return false;

	query.first();

	return query.value("remember_pass").toBool();
}

/***************************************************
*从本地数据库通过帐号获取密码
****************************************************
*/
QString Database::getPassByUsername(QString username)
{
	QSqlQuery query(db);
	QString str(QString("SELECT userpass FROM TABLE_USER_PASS WHERE username='%1';")
		.arg(username)
	);

	if (!query.exec(str))
	{
		qDebug() << query.lastError();
		return QString();
	}
		

	query.first();

	return query.value("userpass").toString();
}

void Database::saveFilesToLocal(const QString & path, const QList<FileObject*>& files)
{
	QString file_path_md5 = JYunTools::stringMD5(path);

	QSqlQuery query(db);
	query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'(%2, %3, %4);")\
		.arg("TABLE_FILE_CHCHE")
		.arg("file_path VARCHAR(32) PRIMARY KEY NOT NULL")
		.arg("file_list TEXT NOT NULL")
		.arg("keep_time DATETIME NOT NULL")
	);

	QString file_list;
	QJsonArray jsonArray;

	for (const FileObject *file : files)
	{
		QJsonObject jsonObject;
		jsonObject.insert("name", file->fileName());
		jsonObject.insert("type", (int)(file->fileType()));
		jsonObject.insert("date", file->dateTime().toSecsSinceEpoch());

		if (file->fileType() != FileType::Folder)
		{
			jsonObject.insert("size", (qint64)((File *)file)->fileSize());
			jsonObject.insert("md5", ((File *)file)->md5());
		}

		jsonArray.append(jsonObject);
	}
	QJsonDocument document(jsonArray);

	file_list = document.toJson();

	//存在则更新，不存在则插入
	query.prepare("REPLACE INTO TABLE_FILE_CHCHE(file_path, file_list, keep_time) VALUES(?, ?, ?)");
	query.bindValue(0, file_path_md5);
	query.bindValue(1, file_list);
	query.bindValue(2, QDateTime::currentDateTime());
	query.exec();

	db.commit();
}

void Database::saveFilesToLocal(const QString & path, const QByteArray & bytearray)
{
	if (bytearray.isEmpty())
		return;

	QString file_path_md5 = JYunTools::stringMD5(path);

	QSqlQuery query(db);
	query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'(%2, %3, %4);")\
		.arg("TABLE_FILE_CHCHE")
		.arg("file_path VARCHAR(32) PRIMARY KEY NOT NULL")
		.arg("file_list TEXT NOT NULL")
		.arg("keep_time DATETIME NOT NULL")
	);

	//存在则更新，不存在则插入
	query.prepare("REPLACE INTO TABLE_FILE_CHCHE(file_path, file_list, keep_time) VALUES(?, ?, ?)");
	query.bindValue(0, file_path_md5);
	query.bindValue(1, bytearray);
	query.bindValue(2, QDateTime::currentDateTime());
	query.exec();

	db.commit();
}

QByteArray Database::getFilesFromLocal(const QString & path)
{
	QString file_path_md5 = JYunTools::stringMD5(path);
	QSqlQuery query(db);
	QString str(QString("SELECT file_list FROM TABLE_FILE_CHCHE WHERE file_path='%1';")
		.arg(file_path_md5)
	);

	if (!query.exec(str))
		return QByteArray();

	if (!query.size())
		return QByteArray();

	query.first();

	return query.value("file_list").toByteArray();
}

bool Database::isLocalCacheValid(const QString & path)
{
	QString file_path_md5 = JYunTools::stringMD5(path);
	QSqlQuery query(db);
	QString str(QString("SELECT keep_time FROM TABLE_FILE_CHCHE WHERE file_path='%1';")
		.arg(file_path_md5)
	);

	if (!query.exec(str))
		return false;

	if (!query.size())
		return false;

	query.first();

	QDateTime date = query.value("keep_time").toDateTime();

	qint64 sec = QDateTime::currentSecsSinceEpoch() - date.toSecsSinceEpoch();

	if (sec > 24 * 60 * 60)
		return false;

	return true;
}

void Database::setDownloadPath(const QString & path)
{
	QSqlQuery query(db);

	query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'(%2);")\
		.arg("DOWNLOAD_PATH")
		.arg("download_path TEXT PRIMARY KEY NOT NULL")
	);

	//存在则更新，不存在则插入
	query.exec(QString("REPLACE INTO DOWNLOAD_PATH(download_path) VALUES('%1');")
		.arg(path)
	);

	db.commit();
}

QString Database::getDownloadPath()
{
	QSqlQuery query(db);
	QString str("SELECT download_path FROM DOWNLOAD_PATH;");
	
	if (!query.exec(str))
		return QDir::currentPath();

	query.first();

	return query.value("download_path").toString();
}

