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
	connect(downloadAct, &QAction::triggered, this, [this]() {
		download();
	});
	m_pMenu->addAction(downloadAct);

	m_pMenu->addSeparator();

	QAction *shareAct = new QAction("����", this);
	connect(shareAct, &QAction::triggered, this, [this]() {
		share();
	});
	m_pMenu->addAction(shareAct);

	m_pMenu->addSeparator();

	QAction *copyAct = new QAction("����", this);
	connect(copyAct, &QAction::triggered, this, [this]() {
		copy();
	});
	m_pMenu->addAction(copyAct);

	QAction *cutAct = new QAction("����", this);
	connect(cutAct, &QAction::triggered, this, [this]() {
		cut();
	});
	m_pMenu->addAction(cutAct);

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
