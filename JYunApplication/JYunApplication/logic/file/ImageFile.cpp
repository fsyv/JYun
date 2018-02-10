#include "stdafx.h"
#include "logic\file\ImageFile.h"


ImageFile::ImageFile() :
	File(FileType::Image)
{
	init();
}


ImageFile::~ImageFile()
{
}

void ImageFile::init()
{

}

bool ImageFile::isImageFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("ImageFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}
