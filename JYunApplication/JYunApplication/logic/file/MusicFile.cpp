#include "stdafx.h"
#include "MusicFile.h"


MusicFile::MusicFile(Folder *parent) :
	File(FileType::Music, parent)
{
	
}


MusicFile::~MusicFile()
{
}

bool MusicFile::preview()
{
	return false;
}


bool MusicFile::isMusicFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("MusicFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}
