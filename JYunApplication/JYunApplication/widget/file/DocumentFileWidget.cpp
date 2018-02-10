#include "stdafx.h"
#include "DocumentFileWidget.h"

#include "logic\file\DocumentFile.h"

DocumentFileWidget::DocumentFileWidget(DocumentFile *file, QWidget *parent):
	FileWidget(file, parent)
{
	init();
}


DocumentFileWidget::~DocumentFileWidget()
{
}

void DocumentFileWidget::initMenu()
{
	//ÎÄ¼þ¼ÐÓÒ¼ü²Ëµ¥
	// 1.Ô¤ÀÀ
	// 2.ÏÂÔØ
	// 3.·ÖÏí
	// 4.¸´ÖÆ
	// 5.¼ôÇÐ
	// 6.ÖØÃüÃû
	// 7.É¾³ý
	// 8.ÊôÐÔ
	QAction *openAct = new QAction("Ô¤ÀÀ", this);
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

void DocumentFileWidget::initWidget()
{
	initMenu();
}

void DocumentFileWidget::conn()
{
}

void DocumentFileWidget::initData()
{
	setPicture(":/resource/file/DOCUMENT.png");
}

void DocumentFileWidget::init()
{
	initWidget();

	conn();

	initData();
}

void DocumentFileWidget::mouseDoubleClicked()
{
}
