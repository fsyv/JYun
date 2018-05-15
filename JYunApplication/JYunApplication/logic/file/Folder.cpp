#include "stdafx.h"
#include "Folder.h"

#include "database\Database.h"

#include "logic\network\JYunTcp.h"
#include "logic\file\File.h"

Folder::Folder():
	FileObject(FileType::Folder),
	m_pFileLists(nullptr)
{
	init();
}

Folder::Folder(const Folder & folder):
	FileObject(folder),
	m_pFileLists(nullptr)
{
	setAbsolutePath(folder.absolutePath());

	refresh();
}

Folder::~Folder()
{
	if (m_pFileLists)
		delete m_pFileLists;
	m_pFileLists = nullptr;
}

void Folder::setAbsolutePath(const Folder & folder)
{
	m_stAbsolutePath.append(folder.fileName() + "/");
}

void Folder::setAbsolutePath(const QString & absolutePath)
{
	m_stAbsolutePath = absolutePath;
}

void Folder::addFile(FileObject * file)
{
	QList<FileObject *> *files = fileList();

	files->append(file);

	((Folder *)file)->setParentFolder(this);
}

QList<FileObject*> *Folder::fileList()
{
	//文件列表一级缓存

	if (isRefresh())
		refresh();

	return m_pFileLists;
}

QList<FileObject *> Folder::dumpFileLists(const QByteArray & byte)
{
	QList<FileObject*> files;

	QJsonDocument jsonDocument = QJsonDocument::fromJson(byte);

	if (!byte.isNull())
	{
		QJsonArray jsonArray = jsonDocument.array();

		for (const QJsonValue &jsonValue : jsonArray)
		{
			QJsonObject jsonObject = jsonValue.toObject();

			int type = jsonObject.value("type").toInt();

			FileObject *file = FileObject::createFile((FileType)type);

			if (file->fileType() != FileType::Folder)
			{
				QString md5 = jsonObject.value("md5").toString();
				quint64 size = jsonObject.value("size").toVariant().toULongLong();

				((File *)file)->setMd5(md5);
				((File *)file)->setFileSize(size);
			}

			QString name = jsonObject.value("name").toString();
			QDateTime date = jsonObject.value("date").toVariant().toDateTime();

			file->setFileName(name);
			file->setDateTime(date);

			files.append(file);
		}
	}

	return files;
}

QByteArray Folder::filesToJson()
{
	return QByteArray();
}

QString Folder::absolutePath() const
{
	return m_stAbsolutePath;
}

Folder * Folder::getRootFolder()
{
	Folder *parent = this;

	while (parent != parent->parentFolder())
		parent = parent->parentFolder();

	return parent;
}

void Folder::update()
{
	m_RefreshDateTime = QDateTime::currentDateTime();
	QList<FileObject *> files = getFilesFromServer();
	m_pFileLists->append(files);
}

QDateTime Folder::refreshDateTime() const
{
	return m_RefreshDateTime;
}

QString Folder::filePath()
{
	QString path = absolutePath();
	return path.mid(path.indexOf(":") + 1);
}

bool Folder::download()
{
	//文件夹的下载方法
	//下载文件夹内所有文件

	if (!m_pFileLists)
		fileList();

	for (FileObject *file : *m_pFileLists)
		emit task(file, false);

	return true;
}

bool Folder::upload()
{
	//文件夹的下载方法
	//上传文件夹内所有文件
	//不过好像这个方法没什么用 - -.

	for (FileObject *file : *m_pFileLists)
		file->upload();

	return true;
}

bool Folder::deleted()
{
	if (!m_pFileLists)
		fileList();

	for (FileObject *file : *m_pFileLists)
		file->deleted();

	return true;
}

bool Folder::delect(FileObject * file)
{
	file->deleted();

	QList<FileObject*> *files = fileList();

	files->removeOne(file);

	return true;
}

bool Folder::rename(QString name)
{
	setFileName(name);
	uploadFils();
	return true;
}

bool Folder::uploadFils()
{
	QByteArray json = filesToJson();

	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	tcp->sendPutFileListMsg(absolutePath(), json);

	return true;
}

Folder * Folder::createRootFolder(const QString &username)
{
	Folder *folder = new Folder;
	folder->setParentFolder(folder);
	folder->setAbsolutePath(username + ":/");
	folder->setFileName("根目录");
	return folder;
}

void Folder::init()
{
	
}

bool Folder::isRefresh()
{
	//需要刷新条件
	// 1.如果文件列表指针为空，说明还没获取过文件
	// 2.如果继上次刷新时间超过4个小时，则刷新。
	qint64 date = QDateTime::currentDateTime().currentSecsSinceEpoch() - m_RefreshDateTime.currentSecsSinceEpoch();
	if (!m_pFileLists || date > 4 * 60 * 60)
		return true;

	return false;
}

void Folder::refresh()
{
	m_RefreshDateTime = QDateTime::currentDateTime();

	QList<FileObject *> files;

	if (!m_pFileLists)
	{
		//获取二级缓存
		m_pFileLists = new QList<FileObject *>;
		files = getFilesFromLocal();
	}
	else
	{
		//获取三级缓存
		files = getFilesFromServer();
	}

	for (auto file : files)
	{
		file->setParentFolder(this);
		
		if (file->fileType() != FileType::Folder)
			((File *)file)->getRemoteUrl();
	}

	m_pFileLists->append(files);
}

QList<FileObject *> Folder::getFilesFromLocal()
{
	//二级缓存
	QList<FileObject *> files;
	//如果本地文件缓存有效就取数据
	//无效或者超时，则通过三级缓存取数据
	if (isLocalCacheValid())
	{
		Database db;
		QByteArray json = db.getFilesFromLocal(m_stAbsolutePath);
		files = dumpFileLists(json); 
	}
	else
		files = getFilesFromServer();

	return files;
}

void Folder::cacheFilesToLocal()
{
	//保存到本地
	Database db;
	db.saveFilesToLocal(m_stAbsolutePath, *m_pFileLists);
}

void Folder::cacheFilesToLocal(const QByteArray & byte)
{
	//保存到本地
	Database db;
	db.saveFilesToLocal(m_stAbsolutePath, byte);
}

bool Folder::isLocalCacheValid()
{
	Database db;
	return db.isLocalCacheValid(m_stAbsolutePath);
}

QList<FileObject *> Folder::getFilesFromServer()
{
	//三级缓存
	m_pFileLists->clear();

	JYunTcp *network = GlobalParameter::getInstance()->getTcpNetwork();
	QByteArray byteArray = network->sendGetFileListsMsg(absolutePath());
	QList<FileObject *> files = dumpFileLists(byteArray);

	sortFiles(files);

	//缓存到本地
	cacheFilesToLocal(byteArray);
	return files;
}

void Folder::sortFiles(QList<FileObject *> &files)
{
	//排序规则
	//文件夹在前
	//文件在后
	//按字母顺序排序
}


