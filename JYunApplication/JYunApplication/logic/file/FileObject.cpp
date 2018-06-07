#include "stdafx.h"
#include "FileObject.h"

#include "DocumentFile.h"
#include "ImageFile.h"
#include "MusicFile.h"
#include "VideoFile.h"
#include "OtherFile.h"
#include "Folder.h"

FileObject::FileObject(const FileType &type, Folder *parent):
	m_eFileType(type),
	m_pParentFolder(parent)
{
	
}

FileObject::FileObject(const FileObject & file):
	FileObject(file.fileType())
{
	setFileName(file.fileName());
	setParentFolder(file.parentFolder());
}

FileObject::~FileObject()
{
	
}

void FileObject::setFileName(const QString & name)
{
	m_stFileName = name;
}

void FileObject::clear()
{
	
}

void FileObject::setDateTime(QDateTime date)
{
	m_FileDateTime = date;
}

QDateTime FileObject::dateTime() const
{
	return m_FileDateTime;
}

FileType FileObject::fileType() const
{
	return m_eFileType;
}

QString FileObject::fileName() const
{
	return m_stFileName;
}

QString FileObject::fileNamePath()
{
	return filePath() + "/" + fileName();
}

void FileObject::setParentFolder(Folder * folder)
{
	m_pParentFolder = folder;
}

Folder * FileObject::parentFolder() const
{
	return m_pParentFolder;
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

