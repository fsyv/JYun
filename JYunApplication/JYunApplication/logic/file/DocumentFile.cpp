#include "stdafx.h"
#include "DocumentFile.h"


DocumentFile::DocumentFile(QString name, QListWidget *parent):
	File(name, FileType::Document, parent)
{
	init();
}


DocumentFile::~DocumentFile()
{
}

void DocumentFile::initMenu()
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

void DocumentFile::initWidget()
{
	initMenu();
}

void DocumentFile::conn()
{
}

void DocumentFile::initData()
{
	setPicture(":/resource/file/DOCUMENT.png");
}

void DocumentFile::init()
{
	initWidget();

	conn();

	initData();
}

void DocumentFile::mouseDoubleClicked()
{
}
