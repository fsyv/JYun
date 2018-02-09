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
	//�ļ����Ҽ��˵�
	// 1.����
	// 2.����
	// 3.����
	// 4.����
	// 5.����
	// 6.������
	// 7.ɾ��
	// 8.����
	QAction *openAct = new QAction("����", this);
	m_pMenu->addAction(openAct);

	m_pMenu->addSeparator();

	QAction *downloadAct = new QAction("����", this);
	m_pMenu->addAction(downloadAct);

	QAction *shareAct = new QAction("����", this);
	m_pMenu->addAction(shareAct);

	m_pMenu->addSeparator();

	QAction *copyAct = new QAction("����", this);
	m_pMenu->addAction(copyAct);

	QAction *cutAct = new QAction("����", this);
	m_pMenu->addAction(cutAct);

	m_pMenu->addSeparator();

	QAction *renameAct = new QAction("����", this);
	m_pMenu->addAction(renameAct);

	QAction *delectAct = new QAction("ɾ��", this);
	m_pMenu->addAction(delectAct);

	QAction *propertyAct = new QAction("����", this);
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
