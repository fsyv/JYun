#include "stdafx.h"
#include "VideoFile.h"


VideoFile::VideoFile():
	File(FileType::Video)
{
	
}


VideoFile::~VideoFile()
{
}

bool VideoFile::preview()
{
	//��һҳͼƬ
	return false;
}

bool VideoFile::isVideoFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("VideoFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}
