#include "stdafx.h"
#include "JYunCloudDisk.h"

#include "clouddisk\CloudDiskTopWidget.h"
#include "clouddisk\CloudDiskLeftWidget.h"

JYunCloudDisk::JYunCloudDisk():
	m_pTitle(nullptr),
	m_pTopWidget(nullptr),
	m_pLeftWidget(nullptr)
{
	changeWidgetSize(QSize(800, 600));

	initWidget();
}


JYunCloudDisk::~JYunCloudDisk()
{
}

void JYunCloudDisk::initWidget()
{
	m_pTitle = new QLabel("��ӭʹ��JYun", this);
	m_pTitle->resize(768, 60);
	m_pTitle->move(0, 0);
	m_pTitle->setAlignment(Qt::AlignCenter);
	m_pTitle->setFont(QFont("��������", 25));

	m_pTopWidget = new CloudDiskTopWidget(this);
	m_pTopWidget->move(0, 60);

	m_pLeftWidget = new CloudDiskLeftWidget(this);
	m_pLeftWidget->move(0, 110);
}