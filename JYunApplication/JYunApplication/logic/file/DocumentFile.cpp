#include "stdafx.h"
#include "DocumentFile.h"


DocumentFile::DocumentFile(Folder *parent):
	File(FileType::Document, parent)
{
	
}

DocumentFile::~DocumentFile()
{
}

bool DocumentFile::preview()
{
	//加载前面一部分内容
	return false;
}

bool DocumentFile::isDocumentFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("DocumentFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}
