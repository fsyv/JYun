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

QList<FileObject*> Database::getFilesFromLocal(const QString & path)
{
	QByteArray json = filesJson(path);

	QList<FileObject*> files;

	QJsonDocument jsonDocument = QJsonDocument::fromJson(json);

	if (!json.isNull())
	{
		QJsonArray jsonArray = jsonDocument.array();
		
		for (const QJsonValue &jsonValue : jsonArray)
		{
			QJsonObject jsonObject = jsonValue.toObject();

			int type = jsonObject.value("type").toInt();

			FileObject *file = FileObject::createFile((FileType)type);

			if (file->fileType() != FileType::Folder)
			{
				QString md5 = jsonObject.value("md5").toString();
				quint64 size = jsonObject.value("size").toVariant().toULongLong();

				((File *)file)->setMd5(md5);
				((File *)file)->setFileSize(size);
			}

			QString name = jsonObject.value("name").toString();
			QDateTime date = jsonObject.value("date").toVariant().toDateTime();

			file->setFileName(name);
			file->setDateTime(date);

			files.append(file);
		}
	}

	return files;
}

bool Database::isLocalCacheValid(const QString & path)
{
	QByteArray json = filesJson(path);
	if (json.isEmpty())
		return false;
	return true;
}

QByteArray Database::filesJson(const QString & path)
{
	QString file_path_md5 = JYunTools::stringMD5(path);
	QSqlQuery query(db);
	QString str(QString("SELECT * FROM TABLE_FILE_CHCHE WHERE file_path='%1';")
		.arg(file_path_md5)
	);

	if (!query.exec(str))
		return QByteArray();

	if (!query.size())
		return QByteArray();

	query.first();

	QDateTime date = query.value("keep_time").toDateTime();

	qint64 sec = QDateTime::currentSecsSinceEpoch() - date.toSecsSinceEpoch();

	if (sec > 24 * 60 * 60)
		return QByteArray();

	return query.value("file_list").toByteArray();
}
