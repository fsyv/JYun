#include "stdafx.h"
#include "FolderWidget.h"

#include "logic\file\Folder.h"

FolderWidget::FolderWidget(Folder *folder, QWidget *parent):
	FileObjectWidget(folder, parent)
{
	init();
}

FolderWidget::~FolderWidget()
{
	
}

void FolderWidget::initMenu()
{
	//文件夹右键菜单
	// 1.打开
	// 2.下载
	// 3.分享
	// 4.复制
	// 5.剪切
	// 6.重命名
	// 7.删除
	// 8.属性
	QAction *openAct = new QAction("打开", this);
	connect(openAct, &QAction::triggered, this, [this]() {
		mouseDoubleClicked();
	});
	m_pMenu->addAction(openAct);

	m_pMenu->addSeparator();

	QAction *downloadAct = new QAction("下载", this);
	connect(downloadAct, &QAction::triggered, this, [this]() {
		download();
	});
	m_pMenu->addAction(downloadAct);

	m_pMenu->addSeparator();

	QAction *renameAct = new QAction("改名", this);
	connect(renameAct, &QAction::triggered, this, [this]() {
		rename();
	});
	m_pMenu->addAction(renameAct);

	QAction *delectAct = new QAction("删除", this);
	connect(delectAct, &QAction::triggered, this, [this]() {
		deleted();
	});
	m_pMenu->addAction(delectAct);
}

void FolderWidget::initWidget()
{
	initMenu();
}

void FolderWidget::conn()
{
	
}

void FolderWidget::initData()
{
	setPicture(QString(":/resource/file/FOLDER.png"));
}

void FolderWidget::init()
{
	initWidget();

	conn();

	initData();
}

void FolderWidget::connFiles(QList<FileObject*>& files)
{
	
}
