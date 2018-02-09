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
	//ÎÄ¼þ¼ÐÓÒ¼ü²Ëµ¥
	// 1.ä¯ÀÀ
	// 2.ÏÂÔØ
	// 3.·ÖÏí
	// 4.¸´ÖÆ
	// 5.¼ôÇÐ
	// 6.ÖØÃüÃû
	// 7.É¾³ý
	// 8.ÊôÐÔ
	QAction *openAct = new QAction("ä¯ÀÀ", this);
	m_pMenu->addAction(openAct);

	m_pMenu->addSeparator();

	QAction *downloadAct = new QAction("ÏÂÔØ", this);
	m_pMenu->addAction(downloadAct);

	QAction *shareAct = new QAction("·ÖÏí", this);
	m_pMenu->addAction(shareAct);

	m_pMenu->addSeparator();

	QAction *copyAct = new QAction("¸´ÖÆ", this);
	m_pMenu->addAction(copyAct);

	QAction *cutAct = new QAction("¼ôÇÐ", this);
	m_pMenu->addAction(cutAct);

	m_pMenu->addSeparator();

	QAction *renameAct = new QAction("¸ÄÃû", this);
	m_pMenu->addAction(renameAct);

	QAction *delectAct = new QAction("É¾³ý", this);
	m_pMenu->addAction(delectAct);

	QAction *propertyAct = new QAction("ÊôÐÔ", this);
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
