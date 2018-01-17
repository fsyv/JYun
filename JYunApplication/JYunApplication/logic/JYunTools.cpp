#include "stdafx.h"
#include "JYunTools.h"


JYunTools::JYunTools()
{
}


JYunTools::~JYunTools()
{
}

/***************************************************
*json数组转换为Map
****************************************************
*/
QMap<QString, QString> JYunTools::jsonToMap(const QByteArray & bytearray)
{
	QMap<QString, QString> map;

	QJsonDocument document = QJsonDocument::fromJson(bytearray);

	if (!document.isNull())
	{
		QJsonObject json = document.object();

		QStringList strings = json.keys();

		for (const QString &string : strings)
			map.insert(string, json.value(string).toString());
	}

	return map;
}

/***************************************************
*Map转换为json数组
****************************************************
*/
QByteArray JYunTools::mapToJson(const QMap<QString, QString>& map)
{
	QJsonObject json;

	;
	for(QMap<QString, QString>::const_iterator it = map.constBegin();
		it != map.constEnd(); ++it)
		json.insert(it.key(), it.value());

	QJsonDocument document(json);

	return document.toJson();
}
