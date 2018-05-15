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
	//文件夹右键菜单
	// 2.下载
	// 3.分享
	// 4.复制
	// 5.剪切
	// 6.重命名
	// 7.删除
	// 8.属性

	QAction *downloadAct = new QAction("下载", this);
	connect(downloadAct, &QAction::triggered, this, [this]() {
		download();
	});
	m_pMenu->addAction(downloadAct);

	m_pMenu->addSeparator();

	QAction *shareAct = new QAction("分享", this);
	connect(shareAct, &QAction::triggered, this, [this]() {
		share();
	});
	m_pMenu->addAction(shareAct);

	m_pMenu->addSeparator();

	QAction *copyAct = new QAction("复制", this);
	connect(copyAct, &QAction::triggered, this, [this]() {
		copy();
	});
	m_pMenu->addAction(copyAct);

	QAction *cutAct = new QAction("剪切", this);
	connect(cutAct, &QAction::triggered, this, [this]() {
		cut();
	});
	m_pMenu->addAction(cutAct);

	m_pMenu->addSeparator();

	QAction *renameAct = new QAction("改名", this);
	connect(renameAct, &QAction::triggered, this, [this]() {
		rename();
	});
	m_pMenu->addAction(renameAct);

	QAction *delectAct = new QAction("删除", this);
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
