#include "stdafx.h"
#include "JYunHttp.h"

#include"logic\JYunTools.h"

#include "logic\file\FileObject.h"

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
	m_url.setPath("/login/");

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
*获取头像
****************************************************
*/
void JYunHttp::downloadHead(const QString &username)
{
	m_url.setPath("/head/");
	m_url.setQuery(QString("username=") + username);

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

QString JYunHttp::getHeadMd5(const QString & username)
{
	m_url.setPath("/head/md5/");
	m_url.setQuery(QString("username=") + username);

	QNetworkRequest request(m_url);

	QNetworkReply *reply = m_pManager->get(request);

	QEventLoop temp_loop;
	connect(reply, &QNetworkReply::finished, &temp_loop, &QEventLoop::quit);
	temp_loop.exec();

	QString result;

	if (reply->error() == QNetworkReply::NoError)
	{
		return reply->readAll();
	}
	else
	{
		QString string = reply->errorString();
		result = QString();
	}

	reply->deleteLater();
	return result;
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

bool JYunHttp::modifyPass(const QString & username, const QString & userpass)
{
	m_url.setPath("/modify/");

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

	return true;
}

void JYunHttp::downloadFile(const QString & md5, const QString localPath)
{
	m_url.setPath(QString("/file/%1").arg(md5));

	QNetworkRequest request(m_url);

	QNetworkReply *reply = m_pManager->get(request);

	QEventLoop temp_loop;
	connect(reply, &QNetworkReply::finished, &temp_loop, &QEventLoop::quit);
	temp_loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QFileInfo fileInfo(localPath);
		QFile file(fileInfo.path() + "/" + md5);

		if (file.exists())
		{
			//文件已经存在了，应该抛出异常
			//先删掉存在的文件
			file.remove();
		}
		
		if (file.open(QIODevice::WriteOnly))
		{
			file.write(reply->readAll());

			file.rename(fileInfo.fileName());

			file.close();
		}
	}
	else
	{
		QString string = reply->errorString();
	}

	reply->deleteLater();
}

QList<FileObject*> JYunHttp::getFileList(const QString & path)
{
	m_url.setPath("/filelist/");
	m_url.setQuery(QString("path=").append(path));

	QNetworkRequest request(m_url);

	QNetworkReply *reply = m_pManager->get(request);

	QEventLoop temp_loop;
	connect(reply, &QNetworkReply::finished, &temp_loop, &QEventLoop::quit);
	temp_loop.exec();

	QList<FileObject*> files;

	if (reply->error() == QNetworkReply::NoError)
	{
		QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll());
		QJsonArray jsonArray = jsonDocument.array();

		for (const QJsonValue &jsonValue : jsonArray)
		{
			QJsonObject jsonObject = jsonValue.toObject();

			QString name = jsonObject.value("FileName").toString();
			int type = jsonObject.value("FileType").toInt();

			FileObject *file = FileObject::createFile((FileType)type);
			file->setFileName(name);

			files.append(file);
		}
	}
	else
	{
		QString string = reply->errorString();
	}

	reply->deleteLater();
	return files;
}
