#include "stdafx.h"
#include "CloudDiskFileWidget.h"

#include "logic/file/Folder.h"
#include "logic/file/DocumentFile.h"
#include "logic/file/ImageFile.h"
#include "logic/file/MusicFile.h"
#include "logic/file/OtherFile.h"
#include "logic/file/VideoFile.h"

CloudDiskFileWidget::CloudDiskFileWidget(QWidget *parent):
	QListWidget(parent)
{
	resize(700, 450);
	initWidget();
}


CloudDiskFileWidget::~CloudDiskFileWidget()
{
}

void CloudDiskFileWidget::initWidget()
{
	setObjectName("clouddisk_file");

	setViewMode(QListView::IconMode);
	setSpacing(25);

	FileObject *file = new Folder("�ļ���", this);
	setItemWidget(file->item(), file);

	FileObject *file1 = new DocumentFile("�ĵ�", this);
	setItemWidget(file1->item(), file1);

	FileObject *file2 = new ImageFile("ͼƬ", this);
	setItemWidget(file2->item(), file2);

	FileObject *file3 = new MusicFile("����", this);
	setItemWidget(file3->item(), file3);

	FileObject *file4 = new OtherFile("����", this);
	setItemWidget(file4->item(), file4);

	FileObject *file5 = new VideoFile("��Ƶ", this);
	setItemWidget(file5->item(), file5);
}
