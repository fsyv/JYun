#include "stdafx.h"
#include "CloudDiskStatusBar.h"


CloudDiskStatusBar::CloudDiskStatusBar(QWidget *parent):
	QFrame(parent),
	m_pCheckBoxFrame(nullptr),
	m_pSelectAll(nullptr)
{
	resize(700, 40);

	initWidget();
}


CloudDiskStatusBar::~CloudDiskStatusBar()
{
	if (m_pSelectAll)
		delete m_pSelectAll;
	m_pSelectAll = nullptr;

	if (m_pCheckBoxFrame)
		delete m_pCheckBoxFrame;
	m_pCheckBoxFrame = nullptr;
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
	m_pSelectAll->setToolTip("ȫѡ");
}
