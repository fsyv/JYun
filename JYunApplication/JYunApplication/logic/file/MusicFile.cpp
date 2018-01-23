#include "stdafx.h"
#include "MusicFile.h"


MusicFile::MusicFile(QString name, QListWidget *parent) :
	File(name, FileType::Music, parent)
{
	init();
}


MusicFile::~MusicFile()
{
}

void MusicFile::initMenu()
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

void MusicFile::initWidget()
{
	initMenu();
}

void MusicFile::conn()
{
}

void MusicFile::initData()
{
	setPicture(":/resource/file/MUSIC.png");
}

void MusicFile::init()
{
	initWidget();

	conn();

	initData();
}

void MusicFile::mouseDoubleClicked()
{
}
