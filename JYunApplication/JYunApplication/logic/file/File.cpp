#include "stdafx.h"
#include "File.h"

#include "logic/JYunTools.h"
#include "logic/network/JYunHttp.h"

#include "DocumentFile.h"
#include "ImageFile.h"
#include "MusicFile.h"
#include "VideoFile.h"
#include "OtherFile.h"
#include "Folder.h"

File::File(const FileType &type):
	FileObject(type),
	m_pParentFolder(nullptr)
{

}

File::File(const File & file):
	FileObject(file),
	m_pParentFolder(nullptr)
{
	setParentFolder(file.parentFolder());
}

File::~File()
{
	if (m_pParentFolder)
		delete m_pParentFolder;
	m_pParentFolder = nullptr;
}

void File::calcFileMd5()
{
	m_stFileMD5 = JYunTools::fileMD5(fileNamePath());
}

void File::setParentFolder(Folder * folder)
{
	if (folder)
		m_pParentFolder = new Folder(*folder);
	else
		m_pParentFolder = folder;
}

void File::setFileSize(quint64 size)
{
	m_ui64FileSize = size;
}

void File::setUploadDateTime(QDateTime time)
{
	m_uploadDateTime = time;
}

void File::clear()
{
	m_stFileMD5.clear();
	FileObject::clear();
}

QString File::md5()
{
	if (m_stFileMD5.isEmpty())
		calcFileMd5();
	return m_stFileMD5;
}

Folder * File::parentFolder() const
{
	return m_pParentFolder;
}

quint64 File::fileSize() const
{
	return m_ui64FileSize;
}

QDateTime File::uploadDateTime() const
{
	return m_uploadDateTime;
}

File *File::createFile(const QString & filename)
{
	File *file = nullptr;
	QFileInfo fileInfo(filename);

	QString fileSuffix = fileInfo.suffix();

	if (DocumentFile::isDocumentFile(fileSuffix))
		file = new DocumentFile;
	else if (ImageFile::isImageFile(fileSuffix))
		file = new ImageFile;
	else if (MusicFile::isMusicFile(fileSuffix))
		file = new MusicFile;
	else if (VideoFile::isVideoFile(fileSuffix))
		file = new VideoFile;
	else
		file = new OtherFile;

	file->setFileSize(fileInfo.size());

	return file;
}

QString File::fromConfigFileGetSupportSuffix(const QString & key)
{
	QFile file(QDir::currentPath() + "/system/system_config.json");

	if (!file.open(QIODevice::ReadOnly))
	{
		//文件不能打开，抛出异常
		return false;
	}

	QJsonDocument document = QJsonDocument::fromJson(file.readAll());

	file.close();

	if (document.isNull())
	{
		//配置文件异常，抛出异常
		return false;
	}

	QJsonObject jsonObject = document.object().take(QString("FileType")).toObject();
	return jsonObject.take(key).toString();
}
