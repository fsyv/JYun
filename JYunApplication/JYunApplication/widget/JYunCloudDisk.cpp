#include "stdafx.h"
#include "JYunCloudDisk.h"

#include "clouddisk\CloudDiskTopWidget.h"
#include "clouddisk\CloudDiskLeftWidget.h"
#include "clouddisk\CloudDiskStatusBar.h"
#include "clouddisk\CloudDiskFileWidget.h"
#include "clouddisk\CloudDiskSetup.h"
#include "clouddisk\CloudDiskTaskList.h"

#include "logic\file\File.h"
#include "logic\file\Folder.h"

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
	if (m_pTitle)
		delete m_pTitle;
	m_pTitle = nullptr;

	if (m_pTopWidget)
		delete m_pTopWidget;
	m_pTopWidget = nullptr;

	if (m_pLeftWidget)
		delete m_pLeftWidget;
	m_pLeftWidget = nullptr;

	if (m_pStatusBar)
		delete m_pStatusBar;
	m_pStatusBar = nullptr;

	if (m_pFileWidget)
		delete m_pFileWidget;
	m_pFileWidget = nullptr;

	if (m_pSetup)
		delete m_pSetup;
	m_pSetup = nullptr;
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

	m_pTaskList = new CloudDiskTaskList(this);
	m_pTaskList->move(650, 110);
	m_pTaskList->hide();
}

void JYunCloudDisk::conn()
{
	//上方按钮信号槽绑定
	connect(m_pTopWidget, &CloudDiskTopWidget::uploadFile, m_pFileWidget, &CloudDiskFileWidget::uploadFile);
	connect(m_pTopWidget, &CloudDiskTopWidget::backward, m_pFileWidget, &CloudDiskFileWidget::backward);
	connect(m_pTopWidget, &CloudDiskTopWidget::refresh, m_pFileWidget, &CloudDiskFileWidget::refresh);
	connect(m_pTopWidget, &CloudDiskTopWidget::downloadFile, m_pFileWidget, &CloudDiskFileWidget::downloadFile);
	connect(m_pTopWidget, &CloudDiskTopWidget::shareFile, m_pFileWidget, &CloudDiskFileWidget::shareFile);
	connect(m_pTopWidget, &CloudDiskTopWidget::taskListButtonClicked, m_pTaskList, &CloudDiskTaskList::setVisible);
	//状态栏信号槽绑定
	connect(m_pStatusBar, &CloudDiskStatusBar::selectAllChange, m_pFileWidget, &CloudDiskFileWidget::selectAllClick);
	connect(m_pStatusBar, &CloudDiskStatusBar::folderClicked, m_pFileWidget, &CloudDiskFileWidget::stateBarFolderClicked);
	//左边按钮信号槽绑定
	connect(m_pLeftWidget, &CloudDiskLeftWidget::rootClicked, m_pFileWidget, &CloudDiskFileWidget::showRootDirectory);
	connect(m_pLeftWidget, &CloudDiskLeftWidget::fileEchoChange, m_pFileWidget, &CloudDiskFileWidget::fileCategory);
	connect(m_pLeftWidget, &CloudDiskLeftWidget::setupClicked, m_pSetup, [this](bool b) {
		m_pFileWidget->setVisible(!b);
		m_pStatusBar->setVisible(!b);
		m_pSetup->setVisible(b);
	});
	//文件展示界面信号槽绑定
	connect(m_pFileWidget, &CloudDiskFileWidget::enterFolder, m_pStatusBar, &CloudDiskStatusBar::addFolder);
	connect(m_pFileWidget, &CloudDiskFileWidget::task, m_pTaskList, &CloudDiskTaskList::addTask);

	m_pFileWidget->afterConn();
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
