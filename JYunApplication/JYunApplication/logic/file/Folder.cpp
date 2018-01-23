#include "stdafx.h"
#include "Folder.h"

Folder::Folder(QString name, QListWidget * parent):
	FileObject(name, FileType::Folder, parent)
{
	init();
}

Folder::~Folder()
{

}

void Folder::initMenu()
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

void Folder::initWidget()
{
	initMenu();
}

void Folder::conn()
{
}

void Folder::initData()
{
	setPicture(QString(":/resource/file/FOLDER.png"));
}

void Folder::init()
{
	initWidget();

	conn();

	initData();
}

void Folder::mouseDoubleClicked()
{
}