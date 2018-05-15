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
	connect(openAct, &QAction::triggered, this, [this]() {
		mouseDoubleClicked();
	});
	m_pMenu->addAction(openAct);

	m_pMenu->addSeparator();

	QAction *downloadAct = new QAction("ÏÂÔØ", this);
	connect(downloadAct, &QAction::triggered, this, [this]() {
		download();
	});
	m_pMenu->addAction(downloadAct);

	QAction *shareAct = new QAction("·ÖÏí", this);
	connect(shareAct, &QAction::triggered, this, [this]() {
		share();
	});
	m_pMenu->addAction(shareAct);

	m_pMenu->addSeparator();

	QAction *copyAct = new QAction("¸´ÖÆ", this);
	connect(copyAct, &QAction::triggered, this, [this]() {
		copy();
	});
	m_pMenu->addAction(copyAct);

	QAction *cutAct = new QAction("¼ôÇÐ", this);
	connect(cutAct, &QAction::triggered, this, [this]() {
		cut();
	});
	m_pMenu->addAction(cutAct);

	m_pMenu->addSeparator();

	QAction *renameAct = new QAction("¸ÄÃû", this);
	connect(renameAct, &QAction::triggered, this, [this]() {
		rename();
	});
	m_pMenu->addAction(renameAct);

	QAction *delectAct = new QAction("É¾³ý", this);
	connect(delectAct, &QAction::triggered, this, [this]() {
		delect();
	});
	m_pMenu->addAction(delectAct);
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
