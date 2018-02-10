#include "stdafx.h"
#include "VideoFile.h"


VideoFile::VideoFile():
	File(FileType::Video)
{
	init();
}


VideoFile::~VideoFile()
{
}

void VideoFile::init()
{
}

bool VideoFile::isVideoFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("VideoFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}
