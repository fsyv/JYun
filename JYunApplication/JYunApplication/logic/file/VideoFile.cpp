#include "stdafx.h"
#include "VideoFile.h"


VideoFile::VideoFile(QListWidgetItem *item) :
	File(FileType::Video, item)
{
	init();
}


VideoFile::~VideoFile()
{
}

void VideoFile::initMenu()
{
	//文件夹右键菜单
	// 1.播放
	// 2.下载
	// 3.分享
	// 4.复制
	// 5.剪切
	// 6.重命名
	// 7.删除
	// 8.属性
	QAction *openAct = new QAction("播放", this);
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

void VideoFile::initWidget()
{
	initMenu();
}

void VideoFile::conn()
{
}

void VideoFile::initData()
{
	setPicture(":/resource/file/VIDEO.png");
}

void VideoFile::init()
{
	initWidget();

	conn();

	initData();
}

bool VideoFile::isVideoFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("VideoFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}

void VideoFile::mouseDoubleClicked()
{
}
