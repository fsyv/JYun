#include "stdafx.h"
#include "Database.h"

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
*从本地数据库获取用户列表
****************************************************
*/
QStringList Database::getUserLists()
{
	QSqlQuery query(db);
	QString str("SELECT username, remember_pass FROM TABLE_USER_PASS;");
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
bool Database::isAutoLogin()
{
	QSqlQuery query(db);
	QString str("SELECT auto_login FROM TABLE_AUTO_LOGIN;");
	QMap<QString, bool> users;

	if (!query.exec(str))
		return false;

	return query.value("auto_login").toBool();
}
