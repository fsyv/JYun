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
#include "logic/network/JYunTcp.h"

CloudDiskFileWidget::CloudDiskFileWidget(QWidget *parent) :
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
	//创建根目录
	User *user = GlobalParameter::getInstance()->getUser();
	m_pCurrentFolder = Folder::createRootFolder(user->getUsername());
	openFolder(m_pCurrentFolder);
}

void CloudDiskFileWidget::initMenu()
{
	setContextMenuPolicy(Qt::DefaultContextMenu);

	m_pMenu = new QMenu(this);

	//右键菜单
	// 1.新建文件夹
	// 2.上传文件
	// 3.刷新
	// 4.分享

	QAction *newFolderAct = new QAction("新建文件夹");
	connect(newFolderAct, &QAction::triggered, this, &CloudDiskFileWidget::newFolder);
	m_pMenu->addAction(newFolderAct);
	QAction *uploadAct = new QAction("上传");
	connect(uploadAct, &QAction::triggered, this, &CloudDiskFileWidget::upload);
	m_pMenu->addAction(uploadAct);
	QAction *updateAct = new QAction("刷新");
	connect(updateAct, &QAction::triggered, this, &CloudDiskFileWidget::refresh);
	m_pMenu->addAction(updateAct);
	QAction *shareAct = new QAction("分享");
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
		//断开当前文件夹的信号槽
		m_pCurrentFolder = folder;
	}

	//获取当前文件夹下列表
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
				newFileWidget(object);
			}
		}
		else
		{
			newFileWidget(object);
		}

		if (object->fileType() == FileType::Folder)
		{
			connect((Folder *)object, &Folder::task, this, [this](FileObject *o, bool b) {
				emit task(o, b);
			});
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

FileObjectWidget* CloudDiskFileWidget::newFileWidget(FileObject * file)
{
	QListWidgetItem *item = new QListWidgetItem(this);
	item->setSizeHint(QSize(125, 125));
	FileObjectWidget *widget = FileObjectWidget::createWidget(file);
	connect(widget, &FileObjectWidget::doubleClick, this, &CloudDiskFileWidget::fileDoubleClick);
	connect(widget, &FileObjectWidget::delect, this, &CloudDiskFileWidget::delect);
	setItemWidget(item, widget);

	return widget;
}

void CloudDiskFileWidget::fileCategory(int echo)
{
	//文件夹始终会显示
	m_iEcho = echo;

	update();
}

void CloudDiskFileWidget::uploadFile(File *file)
{
	//当前文件夹添加子文件
	m_pCurrentFolder->addFile(file);

	//视图层做处理
	QListWidgetItem *item = new QListWidgetItem(this);
	item->setSizeHint(QSize(125, 125));
	setItemWidget(item, FileObjectWidget::createWidget(file));

	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	QUrl url = tcp->url();
	file->setRemoteUrl(url.host(), 21, QString("/") + file->md5());

	emit task(file, true);
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
	QList<FileObject *> lists;

	for (int i = 0; i < count(); ++i)
	{
		FileObjectWidget *object = (FileObjectWidget *)itemWidget(item(i));
		if (object->getConfirmCheckBoxStatus())
			lists.push_back(object->file());
	}

	if (!lists.empty())
	{
		for (auto file : lists)
			emit task(file, false);
	}
	else
	{
		QString md5 = QInputDialog::getText(nullptr, "文件共享", "请输入分享码");
		if (!md5.isEmpty())
		{
			OtherFile *file = new OtherFile;
			file->setMd5(md5);

			JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
			QUrl url = tcp->url();
			file->setRemoteUrl(url.host(), 21, file->md5());
			file->setLocalUrl(QDir::currentPath() + "/" + file->md5());
			
			emit task(file, false);
		}
	}
}

void CloudDiskFileWidget::shareFile()
{
	QList<FileObject *> lists;

	for (int i = 0; i < count(); ++i)
	{
		FileObjectWidget *object = (FileObjectWidget *)itemWidget(item(i));
		if (object->getConfirmCheckBoxStatus())
			lists.push_back(object->file());
	}

	if (!lists.empty())
	{
		QString string;
		for (auto file : lists)
		{
			if (file->fileType() != FileType::Folder)
			{
				string += QString("文件：") + file->fileName() + "\n";
				string += QString("分享码：") + ((File *)file)->md5() + "\n";
			}
		}

		if (!string.isEmpty())
		{
			QDialog dialog;
			dialog.resize(400, 300);
			QPlainTextEdit text(&dialog);
			text.setReadOnly(true);
			text.move(0, 0);
			text.resize(dialog.size());
			text.setPlainText(string);
			dialog.show();
			dialog.exec();

			return;
		}
	}

	QMessageBox::information(nullptr, "提示", "请选择文件");
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
	folder->setFileName("新建文件夹");
	m_pCurrentFolder->addFile(folder);

	FileObjectWidget *widget = newFileWidget(folder);

	widget->rename();
}

void CloudDiskFileWidget::upload()
{
	QStringList filepaths = QFileDialog::getOpenFileNames(
		this,
		QString("选择文件"),
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

void CloudDiskFileWidget::delect()
{
	update();
}

void CloudDiskFileWidget::selectAllClick(bool flag)
{
	QList<QListWidgetItem *> items = this->items();
	for (QListWidgetItem *item : items)
		((FileObjectWidget *)itemWidget(item))->setConfirmCheckBoxStatus(flag);
}
