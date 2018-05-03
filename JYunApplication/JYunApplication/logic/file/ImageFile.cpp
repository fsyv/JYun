#include "stdafx.h"
#include "logic\file\ImageFile.h"


ImageFile::ImageFile() :
	File(FileType::Image)
{
	
}


ImageFile::~ImageFile()
{
}

bool ImageFile::preview()
{
	//Àı–°Õº
	return false;
}

bool ImageFile::isImageFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("ImageFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}
