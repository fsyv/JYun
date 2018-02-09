#include "stdafx.h"
#include "logic\file\ImageFile.h"


ImageFile::ImageFile(QListWidgetItem *item) :
	File(FileType::Image, item)
{
	init();
}


ImageFile::~ImageFile()
{
}

void ImageFile::initMenu()
{
	//�ļ����Ҽ��˵�
	// 1.���
	// 2.����
	// 3.����
	// 4.����
	// 5.����
	// 6.������
	// 7.ɾ��
	// 8.����
	QAction *openAct = new QAction("���", this);
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

void ImageFile::initWidget()
{
	initMenu();
}

void ImageFile::conn()
{
}

void ImageFile::initData()
{
	setPicture(":/resource/file/IMAGE.png");
}

void ImageFile::init()
{
	initWidget();

	conn();

	initData();
}

bool ImageFile::isImageFile(const QString & fileSuffix)
{
	QStringList suffixs = fromConfigFileGetSupportSuffix(QString("ImageFile")).split(";");

	return suffixs.contains(fileSuffix, Qt::CaseInsensitive);
}

void ImageFile::mouseDoubleClicked()
{
}
