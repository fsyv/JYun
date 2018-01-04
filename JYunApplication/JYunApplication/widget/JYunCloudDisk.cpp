#include "stdafx.h"
#include "JYunCloudDisk.h"

#include "clouddisk\CloudDiskTopWidget.h"

JYunCloudDisk::JYunCloudDisk():
	m_pTitle(nullptr),
	m_pTopWidget(nullptr)
{
	changeWidgetSize(QSize(800, 600));

	initWidget();
}


JYunCloudDisk::~JYunCloudDisk()
{
}

void JYunCloudDisk::initWidget()
{
	m_pTitle = new QLabel("欢迎使用JYun", this);
	m_pTitle->resize(768, 60);
	m_pTitle->move(0, 0);
	m_pTitle->setAlignment(Qt::AlignCenter);
	m_pTitle->setFont(QFont("方正舒体", 25));

	m_pTopWidget = new CloudDiskTopWidget(this);
	m_pTopWidget->move(0, 60);
}