#include "stdafx.h"
#include "JYunTools.h"


JYunTools::JYunTools()
{
}


JYunTools::~JYunTools()
{
}

/***************************************************
*json����ת��ΪMap
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
*Mapת��Ϊjson����
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

QByteArray JYunTools::fileMD5(QString filePath)
{
	//QFile localFile(filePath);

	//if (!localFile.open(QFile::ReadOnly))
	//{
	//	return 0;
	//}

	//QCryptographicHash ch(QCryptographicHash::Md5);

	//quint64 totalBytes = 0;
	//quint64 bytesWritten = 0;
	//quint64 bytesToWrite = 0;
	////һ�μ���4M
	//quint64 loadSize = 4 * 1024 * 1024;
	//QByteArray buf;

	//totalBytes = localFile.size();
	//bytesToWrite = totalBytes;

	//while (1)
	//{
	//	if (bytesToWrite > 0)
	//	{
	//		buf = localFile.read(qMin(bytesToWrite, loadSize));
	//		ch.addData(buf);
	//		bytesWritten += buf.length();
	//		bytesToWrite -= buf.length();
	//		buf.resize(0);
	//	}
	//	else
	//	{
	//		break;
	//	}

	//	if (bytesWritten == totalBytes)
	//	{
	//		break;
	//	}
	//}

	//localFile.close();
	QFile file(filePath);

	if (!file.open(QIODevice::ReadOnly))
	{
		//�ļ�����������
		return 0;
	}

	QByteArray md5 = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex();

	file.close();

	return md5;
}

QByteArray JYunTools::stringMD5(QString string)
{
	return QCryptographicHash::hash(string.toUtf8(), QCryptographicHash::Md5).toHex();
}

/***************************************************
*�ֽ��뱣��Ϊ����ͼƬ
****************************************************
*/
void JYunTools::byteToLocalImage(const QString &filePath, const QByteArray & byte)
{
	QFile file(filePath);

	if (file.exists())
		file.remove();

	if (!file.open(QIODevice::WriteOnly))
		return;

	file.write(byte);
	file.close();
}
