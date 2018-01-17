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
*�õ�¼ʱ���û�����
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

	//��������£������������
	query.exec(QString("REPLACE INTO TABLE_LOGIN_CONFIG(username, remember_pass, auto_login) VALUES('%1', '%2', '%3');")
		.arg(username)
		.arg(rememberpass)
		.arg(autologin)
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
		.arg("username VARCHAR(16) PRIMARY KEY NOT NULL")
		.arg("userpass VARCHAR(32)")
	);

	//��������£������������
	query.exec(QString("REPLACE INTO TABLE_USER_PASS(username, userpass) VALUES('%1','%2');")
		.arg(username)
		.arg(userpass)
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
*�ӱ������ݿ��ȡ�Ƿ��Զ���¼
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
*�ӱ������ݿ��ȡ�Ƿ��ס����
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
*�ӱ������ݿ�ͨ���ʺŻ�ȡ����
****************************************************
*/
QString Database::getPassByUsername(QString username)
{
	QSqlQuery query(db);
	QString str(QString("SELECT userpass FROM TABLE_USER_PASS WHERE username='%1';")
		.arg(username)
	);

	if (!query.exec(str))
		return QString();

	query.first();

	return query.value("userpass").toString();
}
