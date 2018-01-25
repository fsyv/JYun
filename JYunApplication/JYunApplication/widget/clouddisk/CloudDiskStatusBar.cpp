#include "stdafx.h"
#include "CloudDiskStatusBar.h"

#include "statusbar/CloudDiskStatusBarChildWidget.h"

CloudDiskStatusBar::CloudDiskStatusBar(QWidget *parent):
	QFrame(parent),
	m_pCheckBoxFrame(nullptr),
	m_pSelectAll(nullptr),
	m_pFolderFrame(nullptr)
{
	resize(700, 40);

	init();
}


CloudDiskStatusBar::~CloudDiskStatusBar()
{
	if (m_pSelectAll)
		delete m_pSelectAll;
	m_pSelectAll = nullptr;

	if (m_pCheckBoxFrame)
		delete m_pCheckBoxFrame;
	m_pCheckBoxFrame = nullptr;

	if (m_pFolderFrame)
		delete m_pFolderFrame;
	m_pFolderFrame = nullptr;
}

void CloudDiskStatusBar::initWidget()
{
	setObjectName("clouddisk_bar");

	m_pCheckBoxFrame = new QFrame(this);
	m_pCheckBoxFrame->setObjectName("clouddisk_bar_frame");
	m_pCheckBoxFrame->resize(40, 40);
	m_pCheckBoxFrame->move(0, 0);

	m_pSelectAll = new QCheckBox(m_pCheckBoxFrame);
	m_pSelectAll->setObjectName("clouddisk_left_checkbox");
	m_pSelectAll->resize(32, 32);
	m_pSelectAll->move(4, 4);
	m_pSelectAll->setToolTip("全选");

	m_pFolderFrame = new QFrame(this);
	m_pFolderFrame->setObjectName("clouddisk_bar_frame");
	m_pFolderFrame->resize(660, 40);
	m_pFolderFrame->move(40, 0);

	CloudDiskStatusBarChildWidget *child = new CloudDiskStatusBarChildWidget(CloudDiskStatusBarChildWidget::FolderRole::Root, m_pFolderFrame);
	child->setName("根目录");
	child->move(0, 0);

	CloudDiskStatusBarChildWidget *child1 = new CloudDiskStatusBarChildWidget(CloudDiskStatusBarChildWidget::FolderRole::Other, m_pFolderFrame);
	child1->setName("这是文件夹啊啊");
	child1->move(child->textWidth(), 0);
}

void CloudDiskStatusBar::conn()
{
	connect(m_pSelectAll, &QCheckBox::clicked, this, [this](bool flag) {
		emit selectAllChange(flag);
	});
}

void CloudDiskStatusBar::initData()
{
}

void CloudDiskStatusBar::init()
{
	initWidget();

	conn();

	initData();
}
