#include "stdafx.h"
#include "MusicFile.h"


MusicFile::MusicFile() :
	File(FileType::Music)
{
	init();
}


MusicFile::~MusicFile()
{
}

void MusicFile::init()
{
}

bool MusicFile::isMusicFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("MusicFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}
