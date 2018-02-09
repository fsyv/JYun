#include "stdafx.h"
#include "Folder.h"

#include "database\Database.h"
#include "logic\network\JYunHttp.h"

Folder::Folder(QListWidgetItem *item):
	FileObject(FileType::Folder, item),
	m_pFileLists(nullptr)
{
	init();
}

Folder::Folder(const Folder & folder):
	Folder(folder.item())
{
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

Folder * Folder::createRootFolder(const QString &username)
{
	Folder *folder = new Folder;
	folder->setParentFolder(folder);
	folder->setAbsolutePath(username + ":/");
	folder->setFileName("根目录");
	return folder;
}

void Folder::initMenu()
{
	//文件夹右键菜单
	// 1.打开
	// 2.下载
	// 3.分享
	// 4.复制
	// 5.剪切
	// 6.重命名
	// 7.删除
	// 8.属性
	QAction *openAct = new QAction("打开", this);
	m_pMenu->addAction(openAct);

	m_pMenu->addSeparator();

	QAction *downloadAct = new QAction("下载", this);
	m_pMenu->addAction(downloadAct);

	QAction *shareAct = new QAction("分享", this);
	m_pMenu->addAction(shareAct);

	m_pMenu->addSeparator();

	QAction *copyAct = new QAction("复制", this);
	m_pMenu->addAction(copyAct);

	QAction *cutAct = new QAction("剪切", this);
	m_pMenu->addAction(cutAct);

	m_pMenu->addSeparator();

	QAction *renameAct = new QAction("改名", this);
	m_pMenu->addAction(renameAct);

	QAction *delectAct = new QAction("删除", this);
	m_pMenu->addAction(delectAct);

	QAction *propertyAct = new QAction("属性", this);
	m_pMenu->addAction(propertyAct);
}

void Folder::initWidget()
{
	initMenu();
}

void Folder::conn()
{
	
}

void Folder::initData()
{
	setPicture(QString(":/resource/file/FOLDER.png"));
}

void Folder::init()
{
	initWidget();

	conn();

	initData();
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

	connFiles(files);

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

	JYunHttp http;
	QList<FileObject *> files = http.getFileList(m_stAbsolutePath);

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

void Folder::connFiles(QList<FileObject*>& files)
{
	for (FileObject *object : files)
		if (object->fileType() == FileObject::FileType::Folder)
			connect((Folder *)object, &Folder::open, this, &Folder::openFolder);
}

void Folder::mouseDoubleClicked()
{
	//文件夹双击事件
	//--打开文件夹
	qDebug() << 2;
	emit open(this);
}

void Folder::openFolder(Folder * folder)
{
	qDebug() << 3;
	emit open(folder);
}
