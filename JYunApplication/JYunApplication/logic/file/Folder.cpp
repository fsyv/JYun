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
	//�ļ��б�һ������

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
	folder->setFileName("��Ŀ¼");
	return folder;
}

void Folder::initMenu()
{
	//�ļ����Ҽ��˵�
	// 1.��
	// 2.����
	// 3.����
	// 4.����
	// 5.����
	// 6.������
	// 7.ɾ��
	// 8.����
	QAction *openAct = new QAction("��", this);
	m_pMenu->addAction(openAct);

	m_pMenu->addSeparator();

	QAction *downloadAct = new QAction("����", this);
	m_pMenu->addAction(downloadAct);

	QAction *shareAct = new QAction("����", this);
	m_pMenu->addAction(shareAct);

	m_pMenu->addSeparator();

	QAction *copyAct = new QAction("����", this);
	m_pMenu->addAction(copyAct);

	QAction *cutAct = new QAction("����", this);
	m_pMenu->addAction(cutAct);

	m_pMenu->addSeparator();

	QAction *renameAct = new QAction("����", this);
	m_pMenu->addAction(renameAct);

	QAction *delectAct = new QAction("ɾ��", this);
	m_pMenu->addAction(delectAct);

	QAction *propertyAct = new QAction("����", this);
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
	//��Ҫˢ������
	// 1.����ļ��б�ָ��Ϊ�գ�˵����û��ȡ���ļ�
	// 2.������ϴ�ˢ��ʱ�䳬��4��Сʱ����ˢ�¡�

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
		//��ȡ��������
		m_pFileLists = new QList<FileObject *>;
		files = getFilesFromLocal();
	}
	else
	{
		//��ȡ��������
		files = getFilesFromServer();
	}

	connFiles(files);

	m_pFileLists->append(files);
}

QList<FileObject *> Folder::getFilesFromLocal()
{
	//��������
	QList<FileObject *> files;
	//��������ļ�������Ч��ȡ����
	//��Ч���߳�ʱ����ͨ����������ȡ����
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
	//���浽����
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
	//��������
	m_pFileLists->clear();

	JYunHttp http;
	QList<FileObject *> files = http.getFileList(m_stAbsolutePath);

	sortFiles(files);

	//���浽����
	cacheFilesToLocal();
	return files;
}

void Folder::sortFiles(QList<FileObject *> &files)
{
	//�������
	//�ļ�����ǰ
	//�ļ��ں�
	//����ĸ˳������
}

void Folder::connFiles(QList<FileObject*>& files)
{
	for (FileObject *object : files)
		if (object->fileType() == FileObject::FileType::Folder)
			connect((Folder *)object, &Folder::open, this, &Folder::openFolder);
}

void Folder::mouseDoubleClicked()
{
	//�ļ���˫���¼�
	//--���ļ���
	qDebug() << 2;
	emit open(this);
}

void Folder::openFolder(Folder * folder)
{
	qDebug() << 3;
	emit open(folder);
}
