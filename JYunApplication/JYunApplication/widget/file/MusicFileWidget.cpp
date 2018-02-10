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
