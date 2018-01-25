#include "stdafx.h"
#include "CloudDiskFileWidget.h"

#include "logic/file/Folder.h"
#include "logic/file/DocumentFile.h"
#include "logic/file/ImageFile.h"
#include "logic/file/MusicFile.h"
#include "logic/file/OtherFile.h"
#include "logic/file/VideoFile.h"

CloudDiskFileWidget::CloudDiskFileWidget(QWidget *parent):
	QListWidget(parent),
	m_pFileList(nullptr)
{
	resize(700, 450);

	init();
}


CloudDiskFileWidget::~CloudDiskFileWidget()
{
	if (m_pFileList)
	{
		m_pFileList->clear();
		delete m_pFileList;
		m_pFileList = nullptr;
	}
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
	FileObject *file = new Folder("文件夹", this);
	setItemWidget(file->item(), file);

	FileObject *file1 = new DocumentFile("文档", this);
	setItemWidget(file1->item(), file1);

	FileObject *file2 = new ImageFile("图片", this);
	setItemWidget(file2->item(), file2);

	FileObject *file3 = new MusicFile("音乐", this);
	setItemWidget(file3->item(), file3);

	FileObject *file4 = new OtherFile("其它", this);
	setItemWidget(file4->item(), file4);

	FileObject *file5 = new VideoFile("视频", this);
	setItemWidget(file5->item(), file5);

	m_pFileList = new QList<FileObject *>;
	m_pFileList->append(file);
	m_pFileList->append(file1);
	m_pFileList->append(file2);
	m_pFileList->append(file3);
	m_pFileList->append(file4);
	m_pFileList->append(file5);
}

void CloudDiskFileWidget::init()
{
	initWidget();

	conn();

	initData();
}

void CloudDiskFileWidget::selectAllClick(bool flag)
{
	for(auto object = m_pFileList->begin(); object != m_pFileList->end(); ++object)
		(*object)->setConfirmCheckBoxStatus(flag);
}
