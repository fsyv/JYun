#include "stdafx.h"
#include "FileObject.h"

#include "DocumentFile.h"
#include "ImageFile.h"
#include "MusicFile.h"
#include "VideoFile.h"
#include "OtherFile.h"
#include "Folder.h"

FileObject::FileObject(const FileType &type):
	m_eFileType(type)
{
	init();
}

FileObject::FileObject(const FileObject & file):
	FileObject(file.fileType())
{
	setFileNamePath(file.fileNamePath());
}

FileObject::~FileObject()
{
	
}

void FileObject::setFileName(const QString & name)
{
	m_stFileName = name;
}

void FileObject::setFilePath(const QString & path)
{
	m_stFilePath = path;
}

void FileObject::setFileNamePath(const QString & namePath)
{
	QFileInfo info(namePath);

	setFileName(info.fileName());
	setFilePath(info.path());
}

void FileObject::clear()
{
	m_stFileName.clear();
	m_stFilePath.clear();
}

FileType FileObject::fileType() const
{
	return m_eFileType;
}

QString FileObject::fileName() const
{
	return m_stFileName;
}

QString FileObject::filePath() const
{
	return m_stFilePath;
}

QString FileObject::fileNamePath() const
{
	return filePath() + QString("/") + fileName();
}

FileObject * FileObject::createFile(const FileType & type)
{
	FileObject *object;

	switch (type)
	{
	case FileType::Folder:
		object = new Folder;
		break;
	case FileType::Document:
		object = new DocumentFile;
		break;
	case FileType::Image:
		object = new ImageFile;
		break;
	case FileType::Music:
		object = new MusicFile;
		break;
	case FileType::Video:
		object = new VideoFile;
		break;
	default:
		object = new OtherFile;
		break;
	}
		
	return object;
}

void FileObject::init()
{
}

