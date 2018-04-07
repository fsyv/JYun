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

QDateTime Folder::refreshDateTime() const
{
	return m_RefreshDateTime;
}

Folder * Folder::createRootFolder(const QString &username)
{
	Folder *folder = new Folder;
	folder->setParentFolder(folder);
	folder->setAbsolutePath(username + ":/");
	folder->setFileName("��Ŀ¼");
	return folder;
}

void Folder::init()
{
	
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

	/*JYunHttp http;*/
	QList<FileObject *> files /*= http.getFileList(m_stAbsolutePath)*/;

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

