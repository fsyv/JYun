#include "stdafx.h"
#include "JYunConfig.h"

#include "messagebox\JYunMessageBox.h"

JYunConfig::JYunConfig()
{
	m_strSystemConfig = QString("system/system_config.json");
}

JYunConfig::~JYunConfig()
{
}

bool JYunConfig::load()
{
	if (m_strSystemConfig.isEmpty())
	{
		JYunMessageBox::prompt("配置文件不存在");
		return false;
	}

	QFile config(QDir::currentPath() + "/" + m_strSystemConfig);

	if (!config.open(QIODevice::ReadOnly))
	{
		JYunMessageBox::prompt("无法打开配置文件");
		return false;
	}

	QJsonDocument document = QJsonDocument::fromJson(config.readAll());

	config.close();

	if (document.isNull())
	{
		JYunMessageBox::prompt("无法读取配置文件内容");
		return false;
	}

	QJsonObject jsonObject = document.object().take(QString("configs")).toObject();

	QStringList keys = jsonObject.keys();

	for (const QString &key : keys)
		m_configs[key] = jsonObject[key].toString();

	return true;
}

bool JYunConfig::reload()
{
	m_configs.clear();
	return load();
}

QString JYunConfig::getConfigPath(QString config)
{
	return m_configs.value(config);
}

QJsonValue JYunConfig::getValue(QString config, QString key)
{
	QFile file(QDir::currentPath() + "/" + m_configs[config]);

	if (!file.open(QIODevice::ReadOnly))
	{
		JYunMessageBox::prompt("无法打开配置文件");
		return QJsonObject();
	}

	QJsonDocument document = QJsonDocument::fromJson(file.readAll());

	file.close();

	if (document.isNull())
	{
		JYunMessageBox::prompt("无法读取配置文件内容");
		return QJsonObject();
	}

	return document.object().value(key);
}
