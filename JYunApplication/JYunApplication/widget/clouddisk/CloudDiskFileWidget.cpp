#include "stdafx.h"
#include "CloudDiskFileWidget.h"

#include "logic/GlobalParameter.h"

#include "logic/file/Folder.h"
#include "logic/file/DocumentFile.h"
#include "logic/file/ImageFile.h"
#include "logic/file/MusicFile.h"
#include "logic/file/OtherFile.h"
#include "logic/file/VideoFile.h"

#include "../file/FileObjectWidget.h"
#include "../file/FolderWidget.h"
#include "logic/User.h"

CloudDiskFileWidget::CloudDiskFileWidget(QWidget *parent):
	QListWidget(parent),
	m_pCurrentFolder(nullptr),
	m_iEcho(0)
{
	resize(700, 450);

	init();
}


CloudDiskFileWidget::~CloudDiskFileWidget()
{
	delete m_pCurrentFolder;
}

void CloudDiskFileWidget::afterConn()
{
	initData();
}

void CloudDiskFileWidget::initWidget()
{
	setObjectName("clouddisk_file");

	setViewMode(QListView::IconMode);
	setSpacing(30);
}

void CloudDiskFileWidget::conn()
{

}

void CloudDiskFileWidget::initData()
{
	//������Ŀ¼
	User *user = GlobalParameter::getInstance()->getUser();
	m_pCurrentFolder = Folder::createRootFolder(user->getUsername());
	openFolder(m_pCurrentFolder);
}

void CloudDiskFileWidget::initMenu()
{
	setContextMenuPolicy(Qt::DefaultContextMenu);

	m_pMenu = new QMenu(this);

	//�Ҽ��˵�
	// 1.�½��ļ���
	// 2.�ϴ��ļ�
	// 3.ˢ��
	// 4.����

	QAction *newFolderAct = new QAction("�½��ļ���");
	connect(newFolderAct, &QAction::triggered, this, &CloudDiskFileWidget::newFolder);
	m_pMenu->addAction(newFolderAct);
	QAction *uploadAct = new QAction("�ϴ�");
	connect(uploadAct, &QAction::triggered, this, &CloudDiskFileWidget::upload);
	m_pMenu->addAction(uploadAct);
	QAction *updateAct = new QAction("ˢ��");
	connect(updateAct, &QAction::triggered, this, &CloudDiskFileWidget::refresh);
	m_pMenu->addAction(updateAct);
	QAction *shareAct = new QAction("����");
	connect(shareAct, &QAction::triggered, this, &CloudDiskFileWidget::share);
	m_pMenu->addAction(shareAct);
}

void CloudDiskFileWidget::init()
{
	initWidget();

	conn();

	initMenu();
}

void CloudDiskFileWidget::setFolder(Folder *folder)
{
	if (folder != m_pCurrentFolder)
	{
		//�Ͽ���ǰ�ļ��е��źŲ�
		m_pCurrentFolder = folder;
	}

	//��ȡ��ǰ�ļ������б�
	update();
}

void CloudDiskFileWidget::update()
{
	clear();

	QList<FileObject *> *fileList = m_pCurrentFolder->fileList();

	for (FileObject *object : *fileList)
	{
		if (m_iEcho)
		{
			if ((m_iEcho | (int)(FileType::Folder)) & (int)object->fileType())
			{
				QListWidgetItem *item = new QListWidgetItem(this);
				item->setSizeHint(QSize(125, 125));
				FileObjectWidget *widget = FileObjectWidget::createWidget(object);
				connect(widget, &FileObjectWidget::doubleClick, this, &CloudDiskFileWidget::fileDoubleClick);
				setItemWidget(item, widget);
			}
		}
		else
		{
			QListWidgetItem *item = new QListWidgetItem(this);
			item->setSizeHint(QSize(125, 125));
			FileObjectWidget *widget = FileObjectWidget::createWidget(object);
			connect(widget, &FileObjectWidget::doubleClick, this, &CloudDiskFileWidget::fileDoubleClick);
			setItemWidget(item, widget);
		}
	}
}

QList<QListWidgetItem*> CloudDiskFileWidget::items()
{
	QList<QListWidgetItem *> items;

	int count = this->count();
	for (int i = 0; i < count; ++i)
		items.append(this->item(i));

	return items;
}

void CloudDiskFileWidget::contextMenuEvent(QContextMenuEvent * e)
{
	m_pMenu->move(e->globalPos());
	m_pMenu->show();
}

void CloudDiskFileWidget::fileCategory(int echo)
{
	//�ļ���ʼ�ջ���ʾ
	m_iEcho = echo;

	update();
}

void CloudDiskFileWidget::uploadFile(File *file)
{
	//��ǰ�ļ���������ļ�
	m_pCurrentFolder->addFile(file);

	//��ͼ��������
	QListWidgetItem *item = new QListWidgetItem(this);
	item->setSizeHint(QSize(125, 125));
	setItemWidget(item, FileObjectWidget::createWidget(file));

	//�ļ���ʼ�ϴ�
	file->upload();
}

void CloudDiskFileWidget::backward()
{
	if (m_FolderQueue.size() > 1)
		setFolder(m_FolderQueue.dequeue());
	else
		setFolder(m_FolderQueue.head());
}

void CloudDiskFileWidget::refresh()
{
	m_pCurrentFolder->update();
	update();
}

void CloudDiskFileWidget::downloadFile()
{
}

void CloudDiskFileWidget::shareFile()
{
}

void CloudDiskFileWidget::openFolder(Folder * folder)
{
	qDebug() << 1;
	//��folderѹ��ջ
	m_FolderQueue.push_back(folder);
	setFolder(folder);

	emit enterFolder(m_pCurrentFolder);
}

void CloudDiskFileWidget::stateBarFolderClicked(Folder * folder)
{
	m_FolderQueue.push_back(folder);
	setFolder(folder);
}

void CloudDiskFileWidget::showRootDirectory()
{
	Folder *folder = m_pCurrentFolder->getRootFolder();
	if (folder != m_pCurrentFolder)
		openFolder(folder);
}

void CloudDiskFileWidget::fileDoubleClick(FileObject * file)
{
	if (file->fileType() == FileType::Folder)
		openFolder((Folder *)file);
	else
		((File *)file)->preview();
}

void CloudDiskFileWidget::newFolder()
{
	Folder *folder = new Folder();
	folder->setFileName("�½��ļ���");
	m_pCurrentFolder->addFile(folder);
	QListWidgetItem *item = new QListWidgetItem(this);
	item->setSizeHint(QSize(125, 125));
	FileObjectWidget *widget = new FolderWidget(folder);
	connect(widget, &FileObjectWidget::doubleClick, this, &CloudDiskFileWidget::fileDoubleClick);
	setItemWidget(item, widget);
}

void CloudDiskFileWidget::upload()
{
	QStringList filepaths = QFileDialog::getOpenFileNames(
		this,
		QString("ѡ���ļ�"),
		QDir::homePath().append("/Desktop")
	);

	if (filepaths.isEmpty())
		return;

	for (const auto &filepath : filepaths)
	{
		File *file = File::createFile(filepath);
		file->setLocalUrl(filepath);
		file->setDateTime();

		uploadFile(file);
	}
}

void CloudDiskFileWidget::share()
{
}

void CloudDiskFileWidget::selectAllClick(bool flag)
{
	QList<QListWidgetItem *> items = this->items();
	for(QListWidgetItem *item : items)
		((FileObjectWidget *)itemWidget(item))->setConfirmCheckBoxStatus(flag);
}
