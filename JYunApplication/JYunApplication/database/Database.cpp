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
*���ü�ס����
****************************************************
*/
void Database::setRememberPass(QString username, bool status)
{
	QSqlQuery query(db);

	query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'(%2, %3, %4);")\
		.arg("TABLE_LOGIN_CONFIG")
		.arg("username VARCHAR(16)")
		.arg("remember_pass BOOLEAN")
		.arg("auto_login BOOLEAN")
	);

	QString select = QString("SELECT usename FROM TABLE_LOGIN_CONFIG WHERE usename=%1")
		.arg(username);
	QString update = QString("UPDATE TABLE_LOGIN_CONFIG SET remember_pass=%1 WHERE usename=%2")
		.arg(status)
		.arg(username);
	QString insert = QString("INSERT INTO TABLE_LOGIN_CONFIG(username, remember_pass, auto_login) VALUES(%1,%2,false)")
		.arg(username)
		.arg(status);

	//��������£������������
	query.exec(QString("IF EXISTS (%1) %2 ELSE %2;")
		.arg(select)
		.arg(update)
		.arg(insert)
	);

	db.commit();
}

/***************************************************
*�����Զ���¼
****************************************************
*/
void Database::setAutoLogin(QString username, bool status)
{
	QSqlQuery query(db);
	
	query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'(%2, %3, %4);")\
		.arg("TABLE_LOGIN_CONFIG")
		.arg("username VARCHAR(16)")
		.arg("remember_pass BOOLEAN")
		.arg("auto_login BOOLEAN")
	);

	QString select = QString("SELECT usename FROM TABLE_LOGIN_CONFIG WHERE usename=%1")
		.arg(username);
	QString update = QString("UPDATE TABLE_LOGIN_CONFIG SET auto_login=%1 WHERE usename=%2")
		.arg(status)
		.arg(username);
	QString insert = QString("INSERT INTO TABLE_LOGIN_CONFIG(username, remember_pass, auto_login) VALUES(%1,false,%2)")
		.arg(username)
		.arg(status);

	//��������£������������
	query.exec(QString("IF EXISTS (%1) %2 ELSE %2;")
		.arg(select)
		.arg(update)
		.arg(insert)
	);

	db.commit();
}

/***************************************************
*�����û�������
****************************************************
*/
void Database::setUsernamepass(QString username, QString userpass)
{
	QSqlQuery query(db);

	query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'(%2, %3);")\
		.arg("TABLE_USER_PASS")
		.arg("username VARCHAR(16)")
		.arg("userpass VARCHAR(32)")
	);

	QString select = QString("SELECT usename FROM TABLE_USER_PASS WHERE usename=%1")
		.arg(username);
	QString update = QString("UPDATE TABLE_USER_PASS SET userpass=%1 WHERE usename=%2")
		.arg(userpass)
		.arg(username);
	QString insert = QString("INSERT INTO TABLE_USER_PASS(username, userpass) VALUES(%1,%2)")
		.arg(username)
		.arg(userpass);

	//��������£������������
	query.exec(QString("IF EXISTS (%1) %2 ELSE %2;")
		.arg(select)
		.arg(update)
		.arg(insert)
	);

	db.commit();
}

/***************************************************
*�ӱ������ݿ��ȡ�û��б�
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
*�ӱ������ݿ��ȡ�Ƿ��Զ���¼
****************************************************
*/
bool Database::isAutoLogin(QString username)
{
	QSqlQuery query(db);
	QString str(QString("SELECT auto_login FROM TABLE_LOGIN_CONFIG WHERE username=%1;")
		.arg(username)
	);

	if (!query.exec(str))
		return false;

	return query.value("auto_login").toBool();
}

/***************************************************
*�ӱ������ݿ��ȡ�Ƿ��ס����
****************************************************
*/
bool Database::isRememberPass(QString username)
{
	QSqlQuery query(db);
	QString str(QString("SELECT remember_pass FROM TABLE_LOGIN_CONFIG WHERE username=%1;")
		.arg(username)
	);

	if (!query.exec(str))
		return false;

	return query.value("remember_pass").toBool();
}

/***************************************************
*�ӱ������ݿ�ͨ���ʺŻ�ȡ����
****************************************************
*/
QString Database::getPassByUsername(QString username)
{
	QSqlQuery query(db);
	QString str(QString("SELECT userpass FROM TABLE_USER_PASS WHERE username=%1;")
		.arg(username)
	);

	if (!query.exec(str))
		return QString();

	return query.value("userpass").toString();
}
