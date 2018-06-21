#include "stdafx.h"
#include "CloudDiskTaskList.h"

#include "logic/file/File.h"
#include "widget/clouddisk/tasklist/TaskListChild.h"
#include "logic/network/JYunTcp.h"

CloudDiskTaskList::CloudDiskTaskList(QWidget *parent) :
	QListWidget(parent)
{
	resize(150, 490);

	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}


CloudDiskTaskList::~CloudDiskTaskList()
{
}

void CloudDiskTaskList::initWidget()
{
}

void CloudDiskTaskList::conn()
{
	JYunTcp *tcp = GlobalParameter::getInstance()->getTcpNetwork();
	connect(tcp, &JYunTcp::uploadFileMsg, this, &CloudDiskTaskList::uploadFile);
	connect(tcp, &JYunTcp::downloadFileMsg, this, &CloudDiskTaskList::downloadFile);
}

void CloudDiskTaskList::initData()
{
}

void CloudDiskTaskList::init()
{
	initWidget();
	conn();
	initData();
}

TaskListChild * CloudDiskTaskList::getTaskChildByName(const QString & filename)
{
	return nullptr;
}

void CloudDiskTaskList::newTaskChild(File * file)
{
	QListWidgetItem *item = new QListWidgetItem(this);
	item->setSizeHint(QSize(120, 120));
	TaskListChild *child = new TaskListChild(this);
	child->setLabelName(file->fileName());

	connect((File *)file, &File::loadProgress, child, &TaskListChild::loadProgress);
	connect(child, &TaskListChild::clicked, (File *)file, &File::taskStatus);

	setItemWidget(item, child);
}

void CloudDiskTaskList::uploadFile(QString filename, UploadFileMsg::QueryType type, quint16 port)
{
	TaskListChild *child = getTaskChildByName(filename);

	if (type == UploadFileMsg::Exist)
		child->finished();
	else if (type == UploadFileMsg::NotExist)
	{
		child->setPort(port);
		child->start();
	}
}

void CloudDiskTaskList::downloadFile(QString filename, quint16 port, QString filepath)
{
	TaskListChild *child = getTaskChildByName(filename);
	child->setFilePath(filepath);
	child->setPort(port);
	child->start();
}

void CloudDiskTaskList::addTask(FileObject * file)
{
	if (file->fileType() != FileType::Folder)
	{
		if (m_tasks.contains((File *)file))
			return;

		m_tasks.push_back((File *)file);

		newTaskChild((File *)file);

		if (((File *)file)->processType() == File::ProcessType::Upload)
			file->upload();
		else
			file->download();
	}
	else
		file->download();
}
