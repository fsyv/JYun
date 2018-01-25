#include "stdafx.h"
#include "JYunCloudDisk.h"

#include "clouddisk\CloudDiskTopWidget.h"
#include "clouddisk\CloudDiskLeftWidget.h"
#include "clouddisk\CloudDiskStatusBar.h"
#include "clouddisk\CloudDiskFileWidget.h"
#include "clouddisk\CloudDiskSetup.h"

JYunCloudDisk::JYunCloudDisk():
	m_pTitle(nullptr),
	m_pTopWidget(nullptr),
	m_pLeftWidget(nullptr),
	m_pStatusBar(nullptr),
	m_pFileWidget(nullptr),
	m_pSetup(nullptr)
{
	changeWidgetSize(QSize(800, 600));

	init();
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

	m_pLeftWidget = new CloudDiskLeftWidget(this);
	m_pLeftWidget->move(0, 110);

	m_pStatusBar = new CloudDiskStatusBar(this);
	m_pStatusBar->move(100, 110);

	m_pFileWidget = new CloudDiskFileWidget(this);
	m_pFileWidget->move(100, 150);

	m_pSetup = new CloudDiskSetup(this);
	m_pSetup->move(100, 110);
	m_pSetup->hide();
}

void JYunCloudDisk::conn()
{
	connect(m_pStatusBar, &CloudDiskStatusBar::selectAllChange, m_pFileWidget, &CloudDiskFileWidget::selectAllClick);
	connect(m_pLeftWidget, &CloudDiskLeftWidget::setupClicked, m_pSetup, &CloudDiskSetup::setVisible);
}

void JYunCloudDisk::initData()
{
}

void JYunCloudDisk::init()
{
	initWidget();

	conn();

	initData();
}
