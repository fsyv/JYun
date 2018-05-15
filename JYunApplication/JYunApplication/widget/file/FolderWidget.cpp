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
	connect(openAct, &QAction::triggered, this, [this]() {
		mouseDoubleClicked();
	});
	m_pMenu->addAction(openAct);

	m_pMenu->addSeparator();

	QAction *downloadAct = new QAction("����", this);
	connect(downloadAct, &QAction::triggered, this, [this]() {
		download();
	});
	m_pMenu->addAction(downloadAct);

	m_pMenu->addSeparator();

	QAction *renameAct = new QAction("����", this);
	connect(renameAct, &QAction::triggered, this, [this]() {
		rename();
	});
	m_pMenu->addAction(renameAct);

	QAction *delectAct = new QAction("ɾ��", this);
	connect(delectAct, &QAction::triggered, this, [this]() {
		deleted();
	});
	m_pMenu->addAction(delectAct);
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

void FolderWidget::connFiles(QList<FileObject*>& files)
{
	
}
