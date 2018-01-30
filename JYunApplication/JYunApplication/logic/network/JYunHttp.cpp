#include "stdafx.h"
#include "JYunHttp.h"

#include"logic\JYunTools.h"

JYunHttp::JYunHttp()
{
	m_pManager = new QNetworkAccessManager(this);

	m_url.setScheme("http");
	m_url.setHost("119.29.157.226");
	m_url.setPort(36951);
}


JYunHttp::~JYunHttp()
{
	delete m_pManager;
}

QMap<QString, QString>  JYunHttp::login(const QString & username, const QString & userpass)
{
	m_url.setPath("/login");

	QNetworkRequest request(m_url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
	request.setRawHeader("Authorization", "Bearer 49152bfddae0c5b5d492d3d9871f8c11");

	QMap<QString, QString> login_info;
	login_info["username"] = username;
	login_info["userpass"] = userpass;

	QByteArray json = JYunTools::mapToJson(login_info);

	QNetworkReply *reply = m_pManager->post(request, json);

	QEventLoop temp_loop;
	connect(reply, &QNetworkReply::finished, &temp_loop, &QEventLoop::quit);
	temp_loop.exec();

	QMap<QString, QString> result;

	if (reply->error() == QNetworkReply::NoError)
	{
		QString string = reply->readAll();
		result = JYunTools::jsonToMap(string.toUtf8());
	}
	else
	{
		result["login_error"] = reply->errorString();
	}

	reply->deleteLater();

	return result;
}

/***************************************************
*»ñÈ¡Í·Ïñ
****************************************************
*/
void JYunHttp::downloadHead(const QString &username)
{
	m_url.setPath("/head/");
	m_url.setQuery(QString("user=") + username);

	QNetworkRequest request(m_url);

	QNetworkReply *reply = m_pManager->get(request);

	QEventLoop temp_loop;
	connect(reply, &QNetworkReply::finished, &temp_loop, &QEventLoop::quit);
	temp_loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		JYunTools::byteToLocalImage(QDir::currentPath() + QString("/head/") + username, reply->readAll());
	}
	else
	{
		QString string = reply->errorString();
	}

	reply->deleteLater();
}

void JYunHttp::uploadHead(const QString & username)
{
	//m_url.setPath("/head");

	//QNetworkRequest request(m_url);
	//request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
	//request.setRawHeader("Authorization", "Bearer 49152bfddae0c5b5d492d3d9871f8c11");

	//QMap<QString, QString> login_info;
	//login_info["username"] = username;

	//QByteArray json = JYunTools::mapToJson(login_info);

	//QNetworkReply *reply = m_pManager->post(request, json);

	//QEventLoop temp_loop;
	//connect(reply, &QNetworkReply::finished, &temp_loop, &QEventLoop::quit);
	//temp_loop.exec();

	//if (reply->error() == QNetworkReply::NoError)
	//{
	//	QString string = reply->readAll();
	//}
	//else
	//{
	//	QString string = reply->errorString();
	//}

	//reply->deleteLater();
}

bool JYunHttp::checkUsername(const QString & username)
{
	m_url.setPath("/register/");
	m_url.setQuery(QString("username=") + username);

	QNetworkRequest request(m_url);

	QNetworkReply *reply = m_pManager->get(request);

	QEventLoop temp_loop;
	connect(reply, &QNetworkReply::finished, &temp_loop, &QEventLoop::quit);
	temp_loop.exec();

	bool result;

	if (reply->error() == QNetworkReply::NoError)
	{
		QString string = reply->readAll();
		QMap<QString, QString>map = JYunTools::jsonToMap(string.toUtf8());
		if (map.value("username_state") == QString("True"))
			result = true;
		else if (map.value("username_state") == QString("False"))
			result = false;
	}
	else
	{
		QString string = reply->errorString();
	}

	reply->deleteLater();
	return result;
}

QMap<QString, QString> JYunHttp::registered(const QString & username, const QString & userpass)
{
	m_url.setPath("/register/");

	QNetworkRequest request(m_url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
	request.setRawHeader("Authorization", "Bearer 49152bfddae0c5b5d492d3d9871f8c11");

	QMap<QString, QString> login_info;
	login_info["username"] = username;
	login_info["userpass"] = userpass;

	QByteArray json = JYunTools::mapToJson(login_info);

	QNetworkReply *reply = m_pManager->post(request, json);

	QEventLoop temp_loop;
	connect(reply, &QNetworkReply::finished, &temp_loop, &QEventLoop::quit);
	temp_loop.exec();

	QMap<QString, QString> result;

	if (reply->error() == QNetworkReply::NoError)
	{
		QString string = reply->readAll();
		result = JYunTools::jsonToMap(string.toUtf8());
	}
	else
	{
		result["login_error"] = reply->errorString();
	}

	reply->deleteLater();

	return result;
}
