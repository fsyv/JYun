#include "stdafx.h"
#include "ImageFileWidget.h"

#include "logic\file\ImageFile.h"


ImageFileWidget::ImageFileWidget(ImageFile *file, QWidget *parent):
	FileWidget(file, parent)
{
	init();
}


ImageFileWidget::~ImageFileWidget()
{
}

void ImageFileWidget::initMenu()
{
	//�ļ����Ҽ��˵�
	// 1.���
	// 2.����
	// 3.����
	// 4.����
	// 5.����
	// 6.������
	// 7.ɾ��
	// 8.����
	QAction *openAct = new QAction("���", this);
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
		delect();
	});
	m_pMenu->addAction(delectAct);
}

void ImageFileWidget::initWidget()
{
	initMenu();
}

void ImageFileWidget::conn()
{
}

void ImageFileWidget::initData()
{
	setPicture(":/resource/file/IMAGE.png");
}

void ImageFileWidget::init()
{
	initWidget();

	conn();

	initData();
}

void ImageFileWidget::mouseDoubleClicked()
{
}
