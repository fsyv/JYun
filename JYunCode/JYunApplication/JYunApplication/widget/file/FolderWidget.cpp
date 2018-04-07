#include "stdafx.h"
#include "FolderWidget.h"

#include "logic\file\Folder.h"

FolderWidget::FolderWidget(Folder *folder, QWidget *parent):
	FileObjectWidget(folder, parent)
{
	init();
}

FolderWidget::~FolderWidget()
{
	
}

void FolderWidget::initMenu()
{
	//�ļ����Ҽ��˵�
	// 1.��
	// 2.����
	// 3.����
	// 4.����
	// 5.����
	// 6.������
	// 7.ɾ��
	// 8.����
	QAction *openAct = new QAction("��", this);
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

void FolderWidget::initWidget()
{
	initMenu();
}

void FolderWidget::conn()
{
	
}

void FolderWidget::initData()
{
	setPicture(QString(":/resource/file/FOLDER.png"));
}

void FolderWidget::init()
{
	initWidget();

	conn();

	initData();
}

void FolderWidget::mouseDoubleClicked()
{
	//�ļ���˫���¼�
	//--���ļ���
	emit open((Folder *)m_pFile);
}

void FolderWidget::openFolder(Folder * folder)
{
	
}
