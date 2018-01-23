#include "stdafx.h"
#include "OtherFile.h"


OtherFile::OtherFile(QString name, QListWidget *parent) :
	File(name, FileType::Other, parent)
{
	init();
}


OtherFile::~OtherFile()
{
}

void OtherFile::initMenu()
{
	//文件夹右键菜单
	// 2.下载
	// 3.分享
	// 4.复制
	// 5.剪切
	// 6.重命名
	// 7.删除
	// 8.属性

	QAction *downloadAct = new QAction("下载", this);
	m_pMenu->addAction(downloadAct);

	m_pMenu->addSeparator();

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

void OtherFile::initWidget()
{
	initMenu();
}

void OtherFile::conn()
{
}

void OtherFile::initData()
{
	setPicture(":/resource/file/OTHER.png");
}

void OtherFile::init()
{
	initWidget();

	conn();

	initData();
}

void OtherFile::mouseDoubleClicked()
{
}
