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
#include "logic/network/JYunTcp.h"
#include "logic/User.h"

using namespace std;

File::File(const FileType &type, Folder *parent):
	FileObject(type, parent),
	m_eCurrentProcess(ProcessType::NotProcess)
{
	m_pManager = new QNetworkAccessManager(this);
}

File::File(const File &file):
	FileObject(file)
{
	setParentFolder(file.parentFolder());
	setProcessType(file.processType());
}

File::~File()
{
	if (m_pParentFolder)
		delete m_pParentFolder;
	m_pParentFolder = nullptr;
}

void File::calcFileMd5()
{
	m_stFileMD5 = JYunTools::fileMD5(m_urlLocal.path());
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
	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	QUrl url = tcp->url();
	setRemoteUrl(url.host(), 21, QString("/") + md5());
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

File::ProcessType File::processType() const
{
	return m_eCurrentProcess;
}

void File::setProcessType(const ProcessType & type)
{
	m_eCurrentProcess = type;
}

void File::setDownloadProcess()
{
	setProcessType(ProcessType::Download);
}

void File::setUploadProcess()
{
	setProcessType(ProcessType::Upload);
}

QString File::filePath()
{
	if (m_pParentFolder)
		return m_pParentFolder->filePath();
	else
		return QDir::currentPath();
}

bool File::download()
{
	//若文件url不存在
	//生成url
	//生成本地路径
	//下载

	//future<bool> fun = async(launch::async, [this]()->bool {

	//});

	User *user = GlobalParameter::getInstance()->getUser();
	m_urlLocal = user->getDownloadPath() + "/" + fileName();
	m_pFile = new QFile(m_urlLocal.path());
	m_pFile->open(QIODevice::WriteOnly);

	m_pManager->setNetworkAccessible(QNetworkAccessManager::Accessible);

	QUrl url;
	url.setScheme("ftp");
	url.setHost(m_urlRemote.host());
	url.setPath(QString("/home/fsyv_ftp/") + m_urlRemote.path());
	url.setPort(21);
	url.setUserName("fsyv_ftp");
	url.setPassword("fswoshiCJY11pt");

	QNetworkRequest request(url);
	m_pReply = m_pManager->get(request);

	connect(m_pReply, SIGNAL(readyRead()), this, SLOT(readContent()));
	connect(m_pManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(loadError(QNetworkReply::NetworkError)));
	connect(m_pReply, &QNetworkReply::downloadProgress, this, [this](qint64 c, qint64 t) {
		emit loadProgress(c, t);
	});

	return true;

	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	tcp->sendDownloadFileMsg(md5());
}

bool File::upload()
{
	//计算文件md5
	//查询服务器是否存在文件
	//若存在取文件的前1024kb数据与服务器的进行比对
	//若不存在直接上传

	m_pFile = new QFile(m_urlLocal.path());
	m_pFile->open(QIODevice::ReadOnly);
	QByteArray byte_file = m_pFile->readAll();

	m_pManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
	QUrl url;
	url.setScheme("ftp");
	url.setHost(m_urlRemote.host());
	url.setPath(QString("/home/fsyv_ftp/") + m_urlRemote.path());
	url.setPort(21);
	url.setUserName("fsyv_ftp");
	url.setPassword("fswoshiCJY11pt");

	QNetworkRequest request(url);
	m_pReply = m_pManager->put(request, byte_file);

	connect(m_pManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(loadError(QNetworkReply::NetworkError)));
	connect(m_pReply, &QNetworkReply::uploadProgress, this, [this](qint64 c, qint64 t) {
		emit loadProgress(c, t);
	});


	parentFolder()->uploadFils();
	return true;

	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	tcp->sendUploadFileMsg(md5());
}

bool File::deleted()
{
	parentFolder()->uploadFils();
	return true;

	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	tcp->sendDeleteFileMsg(md5());
}

bool File::rename(QString name)
{
	setFileName(name);
	parentFolder()->uploadFils();

	return true;
}

void File::pause()
{
	if (m_pReply)
	{
		m_pReply->abort();
		m_pReply->deleteLater();
		m_pReply = nullptr;
	}

	if (m_pFile)
	{
		m_pFile->flush();
		m_pFile->close();
		delete m_pFile;
		m_pFile = nullptr;
	}
}

void File::restart()
{
	if (m_eCurrentProcess == ProcessType::Download)
		download();
	else
		upload();
}

bool File::preview()
{
	return false;
}

File *File::createFile(const QString & filename, Folder *parent)
{
	File *file = nullptr;
	QFileInfo fileInfo(filename);

	QString fileSuffix = fileInfo.suffix();

	if (DocumentFile::isDocumentFile(fileSuffix))
		file = new DocumentFile(parent);
	else if (ImageFile::isImageFile(fileSuffix))
		file = new ImageFile(parent);
	else if (MusicFile::isMusicFile(fileSuffix))
		file = new MusicFile(parent);
	else if (VideoFile::isVideoFile(fileSuffix))
		file = new VideoFile(parent);
	else
		file = new OtherFile(parent);

	file->setFileSize(fileInfo.size());

	return file;
}

QString File::fromConfigFileGetSupportSuffix(const QString & key)
{
	JYunConfig *config = GlobalParameter::getInstance()->getConfig();
	return config->getValue("file", key).toString();
}

void File::readContent()
{
	m_pFile->write(m_pReply->readAll());
}

void File::replyFinished(QNetworkReply * reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		reply->deleteLater();
		m_pReply = nullptr;

		if (m_pFile)
		{
			m_pFile->flush();
			m_pFile->close();
			delete m_pFile;
			m_pFile = nullptr;
		}

		emit finished();
	}
}

void File::loadError(QNetworkReply::NetworkError)
{
	if (!m_pReply)
		return;
	QMessageBox::critical(nullptr, "错误", m_pReply->errorString());
}

void File::taskStatus(bool b)
{
	if (b)
		pause();
	else
		restart();
}
