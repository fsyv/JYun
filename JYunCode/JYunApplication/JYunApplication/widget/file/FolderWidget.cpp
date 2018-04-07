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
	m_pMenu->addAction(openAct);

	m_pMenu->addSeparator();

	QAction *downloadAct = new QAction("下载", this);
	m_pMenu->addAction(downloadAct);

	QAction *shareAct = new QAction("分享", this);
	m_pMenu->addAction(shareAct);

	m_pMenu->addSeparator();

	QAction *copyAct = new QAction("复制", this);
	m_pMenu->addAction(copyAct);

	QAction *cutAct = new QAction("剪切", this);
	m_pMenu->addAction(cutAct);

	m_pMenu->addSeparator();

	QAction *renameAct = new QAction("改名", this);
	m_pMenu->addAction(renameAct);

	QAction *delectAct = new QAction("删除", this);
	m_pMenu->addAction(delectAct);

	QAction *propertyAct = new QAction("属性", this);
	m_pMenu->addAction(propertyAct);
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

void FolderWidget::mouseDoubleClicked()
{
	//文件夹双击事件
	//--打开文件夹
	emit open((Folder *)m_pFile);
}

void FolderWidget::openFolder(Folder * folder)
{
	
}
