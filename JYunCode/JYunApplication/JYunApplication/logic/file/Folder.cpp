#include "stdafx.h"
#include "Folder.h"

#include "database\Database.h"

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

void Folder::setParentFolder(Folder * parent)
{
	m_pParentFolder = parent;
}

void Folder::addFile(FileObject * file)
{
	QList<FileObject *> *files = fileList();

	files->append(file);

	((Folder *)file)->setParentFolder(this);
}

Folder * Folder::parentFolder() const
{
	return m_pParentFolder;
}

QList<FileObject*> *Folder::fileList()
{
	//文件列表一级缓存

	if (isRefresh())
		refresh();

	return m_pFileLists;
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
		files = db.getFilesFromLocal(m_stAbsolutePath);
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

bool Folder::isLocalCacheValid()
{
	Database db;
	return db.isLocalCacheValid(m_stAbsolutePath);
}

QList<FileObject *> Folder::getFilesFromServer()
{
	//三级缓存
	m_pFileLists->clear();

	/*JYunHttp http;*/
	QList<FileObject *> files /*= http.getFileList(m_stAbsolutePath)*/;

	sortFiles(files);

	//缓存到本地
	cacheFilesToLocal();
	return files;
}

void Folder::sortFiles(QList<FileObject *> &files)
{
	//排序规则
	//文件夹在前
	//文件在后
	//按字母顺序排序
}

