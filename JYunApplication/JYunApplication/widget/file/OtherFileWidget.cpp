#include "stdafx.h"
#include "OtherFileWidget.h"

#include "logic\file\OtherFile.h"

OtherFileWidget::OtherFileWidget(OtherFile *file, QWidget *parent) :
	FileWidget(file, parent)
{
	init();
}


OtherFileWidget::~OtherFileWidget()
{
}

void OtherFileWidget::initMenu()
{
	//�ļ����Ҽ��˵�
	// 2.����
	// 3.����
	// 4.����
	// 5.����
	// 6.������
	// 7.ɾ��
	// 8.����

	QAction *downloadAct = new QAction("����", this);
	m_pMenu->addAction(downloadAct);

	m_pMenu->addSeparator();

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

void OtherFileWidget::initWidget()
{
	initMenu();
}

void OtherFileWidget::conn()
{
}

void OtherFileWidget::initData()
{
	setPicture(":/resource/file/OTHER.png");
}

void OtherFileWidget::init()
{
	initWidget();

	conn();

	initData();
}

void OtherFileWidget::mouseDoubleClicked()
{
}
