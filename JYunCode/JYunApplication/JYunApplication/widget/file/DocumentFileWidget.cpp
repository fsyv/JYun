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
	//�ļ����Ҽ��˵�
	// 1.Ԥ��
	// 2.����
	// 3.����
	// 4.����
	// 5.����
	// 6.������
	// 7.ɾ��
	// 8.����
	QAction *openAct = new QAction("Ԥ��", this);
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
