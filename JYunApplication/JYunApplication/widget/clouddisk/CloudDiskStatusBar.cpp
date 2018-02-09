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

void CloudDiskStatusBar::addFolder(Folder * folder)
{
	if (!folder)
		//抛出异常
		return;

	CloudDiskStatusBarChildWidget *child = new CloudDiskStatusBarChildWidget(m_pFolderFrame);
	connect(child, &CloudDiskStatusBarChildWidget::clicked, this, &CloudDiskStatusBar::childWidgetClicked);

	if (m_FolderList.isEmpty())
		child->setFolderRole(CloudDiskStatusBarChildWidget::FolderRole::Root);
	else
		child->setFolderRole(CloudDiskStatusBarChildWidget::FolderRole::Other);

	child->setFolder(folder);

	m_FolderList.append(child);

	adjustFolderWidth();
}

void CloudDiskStatusBar::childWidgetClicked(CloudDiskStatusBarChildWidget * child)
{
	if (!child)
		//抛出异常
		return;

	int size = m_FolderList.size();
	for (int i = 0; i < size; ++i)
	{
		if (m_FolderList[i] == child)
		{
			while (m_FolderList.size() > i + 1)
			{
				CloudDiskStatusBarChildWidget *back = m_FolderList.back();
				disconnect(back, &CloudDiskStatusBarChildWidget::clicked, this, &CloudDiskStatusBar::childWidgetClicked);
				delete back;
				m_FolderList.pop_back();
			}

			break;
		}
	}

	adjustFolderWidth();

	emit folderClicked(child->folder());
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

void CloudDiskStatusBar::adjustFolderWidth()
{
	//如果长度大于MAX_WIDTH
	//则将第一次隐藏，重复此过程

	int move = 0;
	for (CloudDiskStatusBarChildWidget *child : m_FolderList)
	{
		if (child->folderRole() != CloudDiskStatusBarChildWidget::FolderRole::NotShow)
			child->move(move, 0);
		move += child->textWidth();
	}
}
