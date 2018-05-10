#include "stdafx.h"
#include "CloudDiskTaskList.h"

#include "logic/file/File.h"
#include "widget/clouddisk/tasklist/TaskListChild.h"

CloudDiskTaskList::CloudDiskTaskList(QWidget *parent) :
	QListWidget(parent)
{
	resize(150, 490);

	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}


CloudDiskTaskList::~CloudDiskTaskList()
{
}

void CloudDiskTaskList::addTask(FileObject * file, bool status)
{
	if (m_tasks.contains(file))
		return;

	if (file->fileType() != FileType::Folder)
	{
		m_tasks.push_back(file);

		QListWidgetItem *item = new QListWidgetItem(this);
		item->setSizeHint(QSize(120, 120));
		TaskListChild *child = new TaskListChild(this);
		child->setLabelName(file->fileName());

		connect((File *)file, &File::loadProgress, child, &TaskListChild::loadProgress);
		connect(child, &TaskListChild::clicked, (File *)file, &File::taskStatus);

		setItemWidget(item, child);
	}

	if (status)
		file->upload();
	else
		file->download();


}
