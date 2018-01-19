#include "stdafx.h"
#include "JYunHttp.h"

#include"logic\JYunTools.h"

JYunHttp::JYunHttp()
{
	m_pManager = new QNetworkAccessManager(this);

	m_url.setScheme("http");
	m_url.setHost("127.0.0.1");
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
void JYunHttp::getHead()
{
}
