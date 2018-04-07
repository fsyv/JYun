#include "stdafx.h"
#include "MusicFileWidget.h"

#include "logic\file\MusicFile.h"

MusicFileWidget::MusicFileWidget(MusicFile *file, QWidget *parent) :
	FileWidget(file, parent)
{
	init();
}


MusicFileWidget::~MusicFileWidget()
{
}

void MusicFileWidget::initMenu()
{
	//ÎÄ¼þ¼ÐÓÒ¼ü²Ëµ¥
	// 1.ÊÔÌý
	// 2.ÏÂÔØ
	// 3.·ÖÏí
	// 4.¸´ÖÆ
	// 5.¼ôÇÐ
	// 6.ÖØÃüÃû
	// 7.É¾³ý
	// 8.ÊôÐÔ
	QAction *openAct = new QAction("ÊÔÌý", this);
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

void MusicFileWidget::initWidget()
{
	initMenu();
}

void MusicFileWidget::conn()
{
}

void MusicFileWidget::initData()
{
	setPicture(":/resource/file/MUSIC.png");
}

void MusicFileWidget::init()
{
	initWidget();

	conn();

	initData();
}

void MusicFileWidget::mouseDoubleClicked()
{
}
