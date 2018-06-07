#include "stdafx.h"
#include "Folder.h"

#include "database\Database.h"

#include "logic\network\JYunTcp.h"
#include "logic\file\File.h"
#include "logic/User.h"

Folder::Folder(Folder *parent):
	FileObject(FileType::Folder, parent),
	m_pFileLists(nullptr)
{
	init();
}

Folder::Folder(const Folder & folder):
	FileObject(folder),
	m_pFileLists(nullptr)
{
	setAbsolutePath();

	refresh();
}

Folder::~Folder()
{
	if (m_pFileLists)
		delete m_pFileLists;
	m_pFileLists = nullptr;
}

void Folder::addFile(FileObject * file)
{
	QList<FileObject *> *files = fileList();

	files->append(file);
}

QList<FileObject*> *Folder::fileList()
{
	//�ļ��б�һ������

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
			QDateTime date = QDateTime::fromTime_t(jsonObject.value("date").toVariant().toUInt());

			file->setFileName(name);
			file->setDateTime(date);

			files.append(file);
		}
	}

	return files;
}

QByteArray Folder::filesToJson()
{
	QList<FileObject*> *files = fileList();

	QJsonArray jsonArray;

	for (const FileObject *file : *files)
	{
		QJsonObject jsonObject;
		jsonObject.insert("name", file->fileName());
		jsonObject.insert("type", (int)(file->fileType()));
		jsonObject.insert("date", (qint64)(file->dateTime().toTime_t()));

		if (file->fileType() != FileType::Folder)
		{
			jsonObject.insert("size", (qint64)((File *)file)->fileSize());
			jsonObject.insert("md5", ((File *)file)->md5());
		}

		jsonArray.append(jsonObject);
	}
	QJsonDocument document(jsonArray);

	return document.toJson(QJsonDocument::Compact);
}

void Folder::setFileName(const QString & name)
{
	FileObject::setFileName(name);

	setAbsolutePath();
}

void Folder::setAbsolutePath()
{
	if (m_pParentFolder)
		m_strAbsolutePath = m_pParentFolder->absolutePath() + "/" + fileName();
	else
	{
		User *user = GlobalParameter::getInstance()->getUser();
		m_strAbsolutePath = user->getUsername().toUpper() +":";
	}
}

QString Folder::absolutePath() const
{
	return m_strAbsolutePath;
}

Folder * Folder::getRootFolder()
{
	Folder *parent = this;

	while (parent->parentFolder())
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
	//�ļ��е����ط���
	//�����ļ����������ļ�

	if (!m_pFileLists)
		fileList();

	for (FileObject *file : *m_pFileLists)
		emit task(file, false);

	return true;
}

bool Folder::upload()
{
	//�ļ����ϴ���ʾ�����ļ���

	QString path = absolutePath();

	//�½�Ŀ¼
	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	tcp->sendNewFolderMsg(path);

	emit fileStatusChange(this);
	return true;
}

bool Folder::deleted()
{
	if (!m_pFileLists)
		fileList();

	for (FileObject *file : *m_pFileLists)
		file->deleted();

	QString path = absolutePath();

	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	tcp->sendDeleteFolderMsg(path);

	emit fileStatusChange(this);
	return true;
}

bool Folder::rename(QString name)
{
	QString oldName = absolutePath();
	setFileName(name);
	QString newName = absolutePath();

	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	tcp->sendRenameFolderMsg(oldName, newName);

	emit fileStatusChange(this);
	return true;
}

bool Folder::delecteFile(FileObject * file)
{
	file->deleted();

	QList<FileObject*> *files = fileList();

	files->removeOne(file);
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
	folder->setAbsolutePath();
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
	//��������
	QList<FileObject *> files;
	//��������ļ�������Ч��ȡ����
	//��Ч���߳�ʱ����ͨ����������ȡ����
	if (isLocalCacheValid())
	{
		Database db;
		QByteArray json = db.getFilesFromLocal(m_strAbsolutePath);
		files = dumpFileLists(json); 
	}
	else
		files = getFilesFromServer();

	return files;
}

void Folder::cacheFilesToLocal()
{
	//���浽����
	Database db;
	db.saveFilesToLocal(m_strAbsolutePath, *m_pFileLists);
}

void Folder::cacheFilesToLocal(const QByteArray & byte)
{
	//���浽����
	Database db;
	db.saveFilesToLocal(m_strAbsolutePath, byte);
}

bool Folder::isLocalCacheValid()
{
	Database db;
	return db.isLocalCacheValid(m_strAbsolutePath);
}

QList<FileObject *> Folder::getFilesFromServer()
{
	//��������
	m_pFileLists->clear();

	JYunTcp *network = GlobalParameter::getInstance()->getTcpNetwork();
	QByteArray byteArray = network->sendGetFileListsMsg(absolutePath());
	QList<FileObject *> files = dumpFileLists(byteArray);

	sortFiles(files);

	//���浽����
	cacheFilesToLocal(byteArray);
	return files;
}

void Folder::sortFiles(QList<FileObject *> &files)
{
	//�������
	//�ļ�����ǰ
	//�ļ��ں�
	//����ĸ˳������
}


