#include "stdafx.h"
#include "File.h"

#include "logic/JYunTools.h"
#include "logic\network\JYunHttp.h"

#include "DocumentFile.h"
#include "ImageFile.h"
#include "MusicFile.h"
#include "VideoFile.h"
#include "OtherFile.h"

File::File(FileType type, QListWidgetItem *item):
	FileObject(type, item)
{

}

File::File(const File & file):
	File(file.fileType(), file.item())
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
	if (m_stFileMD5.isEmpty())
		calcFileMd5();
	return m_stFileMD5;
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
	return file;
}

void File::mouseDoubleClicked()
{
}

void File::upload()
{

}

void File::download()
{
	JYunHttp http;

	http.downloadFile(md5(), QString("e:/JYun_download/") + fileName());
}

void File::clear()
{
	m_stFileMD5.clear();
}

QString File::fromConfigFileGetSupportSuffix(const QString & ksy)
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
	return jsonObject.take(ksy).toString();
}
