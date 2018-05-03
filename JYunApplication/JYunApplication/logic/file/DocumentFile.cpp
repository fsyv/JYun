#include "stdafx.h"
#include "DocumentFile.h"


DocumentFile::DocumentFile():
	File(FileType::Document)
{
	
}

DocumentFile::~DocumentFile()
{
}

bool DocumentFile::preview()
{
	//����ǰ��һ��������
	return false;
}

bool DocumentFile::isDocumentFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("DocumentFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}
