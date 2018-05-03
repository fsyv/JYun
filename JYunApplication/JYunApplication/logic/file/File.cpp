#include "stdafx.h"
#include "File.h"

#include "logic/JYunTools.h"

#include "DocumentFile.h"
#include "ImageFile.h"
#include "MusicFile.h"
#include "VideoFile.h"
#include "OtherFile.h"
#include "Folder.h"

#include "logic/JYunConfig.h"

File::File(const FileType &type):
	FileObject(type)
{

}

File::File(const File & file):
	FileObject(file)
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


void File::setFileSize(quint64 size)
{
	m_ui64FileSize = size;
}

void File::clear()
{
	m_stFileMD5.clear();
	FileObject::clear();
}

void File::setMd5(QString md5)
{
	m_stFileMD5 = md5;
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

void File::getRemoteUrl()
{
	//向服务器发送请求

}

void File::setRemoteUrl(QString url)
{
	m_urlRemote.clear();
	m_urlRemote.setUrl(url);
}

void File::setRemoteUrl(QString host, quint16 port, QString path)
{
	m_urlRemote.setHost(host);
	m_urlRemote.setPort(port);
	m_urlRemote.setPath(path);
}

QUrl File::remoteUrl()
{
	return m_urlRemote;
}

void File::setLocalUrl(QString path)
{
	QFileInfo fileinfo(path);
	setFileName(fileinfo.fileName());

	m_urlLocal.setPath(path);
}

QUrl File::localUrl()
{
	return m_urlLocal;
}

bool File::remove()
{
	QFile file(m_urlLocal.path());
	return file.remove();
}

QString File::filePath()
{
	return m_pParentFolder->filePath();
}

bool File::download()
{
	//若文件url不存在
	//生成url
	//生成本地路径
	//下载

	return false;
}

bool File::upload()
{
	//计算文件md5
	//查询服务器是否存在文件
	//若存在取文件的前1024kb数据与服务器的进行比对
	//若不存在直接上传


	return false;
}

bool File::preview()
{
	return false;
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
	JYunConfig *config = GlobalParameter::getInstance()->getConfig();
	return config->getValue("file", key).toString();
}
