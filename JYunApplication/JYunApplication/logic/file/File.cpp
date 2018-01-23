#include "stdafx.h"
#include "File.h"

#include "logic/JYunTools.h"

File::File(QString name, FileType type, QListWidget *parent):
	FileObject(name, type, parent)
{

}

File::~File()
{
}

void File::calcFileMd5()
{
	m_stFileMD5 = JYunTools::fileMD5(fileNamePath());
}

QString File::md5()
{
	return m_stFileMD5;
}
