#include "stdafx.h"
#include "DocumentFile.h"


DocumentFile::DocumentFile():
	File(FileType::Document)
{
	init();
}

DocumentFile::~DocumentFile()
{
}

void DocumentFile::init()
{

}

bool DocumentFile::isDocumentFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("DocumentFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}
