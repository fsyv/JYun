#include "stdafx.h"
#include "CloudDiskFileWidget.h"

#include "logic/file/Folder.h"
#include "logic/file/DocumentFile.h"
#include "logic/file/ImageFile.h"
#include "logic/file/MusicFile.h"
#include "logic/file/OtherFile.h"
#include "logic/file/VideoFile.h"

#include "../file/FileObjectWidget.h"

CloudDiskFileWidget::CloudDiskFileWidget(QWidget *parent):
	QListWidget(parent),
	m_pCurrentFolder(nullptr)
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
	setSpacing(25);
}

void CloudDiskFileWidget::conn()
{

}

void CloudDiskFileWidget::initData()
{
	//创建根目录
	User *user = User::getInstance();
	user->setUsername("fsyv");
	m_pCurrentFolder = Folder::createRootFolder(user->getUsername());
	openFolder(m_pCurrentFolder);
}

void CloudDiskFileWidget::init()
{
	initWidget();

	conn();
}

void CloudDiskFileWidget::showCategory(int echo)
{
	QList<QListWidgetItem *> items = this->items();
	for (auto item = items.begin(); item != items.end(); ++item)
	{
		FileObjectWidget *fileWidget = (FileObjectWidget *)itemWidget(*item);
		fileWidget->setVisible((int)(fileWidget->file()->fileType()) & echo);
	}
}

void CloudDiskFileWidget::showAll()
{
	QList<QListWidgetItem *> items = this->items();
	for (auto item = items.begin(); item != items.end(); ++item)
		((FileObjectWidget *)itemWidget(*item))->setVisible(true);
}

void CloudDiskFileWidget::setFolder(Folder *folder)
{
	if (folder != m_pCurrentFolder)
	{
		//断开当前文件夹的信号槽
		disconnect(m_pCurrentFolder, &Folder::open, this, &CloudDiskFileWidget::openFolder);
		m_pCurrentFolder = folder;
		connect(m_pCurrentFolder, &Folder::open, this, &CloudDiskFileWidget::openFolder);
	}
	else
		connect(m_pCurrentFolder, &Folder::open, this, &CloudDiskFileWidget::openFolder);

	//获取当前文件夹下列表
	update();
}

void CloudDiskFileWidget::update()
{
	clear();

	QList<FileObject *> *fileList = m_pCurrentFolder->fileList();

	for (FileObject *object : *fileList)
	{
		setItemWidget(new QListWidgetItem(this), FileObjectWidget::createWidget(object));
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

void CloudDiskFileWidget::fileCategory(int echo)
{
	if (echo)
		showCategory(echo);
	else
		showAll();
}

void CloudDiskFileWidget::uploadFile(File *file)
{
	file->setParentFolder(m_pCurrentFolder);
}

void CloudDiskFileWidget::backward()
{
	if (m_FolderQueue.size() > 1)
		setFolder(m_FolderQueue.dequeue());
	else
		setFolder(m_FolderQueue.head());
}

void CloudDiskFileWidget::forward()
{
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
	//把folder压入栈
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

void CloudDiskFileWidget::selectAllClick(bool flag)
{
	QList<QListWidgetItem *> items = this->items();
	for(QListWidgetItem *item : items)
		((FileObjectWidget *)itemWidget(item))->setConfirmCheckBoxStatus(flag);
}
