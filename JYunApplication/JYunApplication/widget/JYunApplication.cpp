#include "stdafx.h"
#include "JYunApplication.h"

#include "messagebox/ApplicationCloseDialog.h"

JYunApplication::JYunApplication(QString username):
	m_pSetupButton(nullptr),
	m_pCloudDiskButton(nullptr),
	m_pBackupButton(nullptr)
{
	changeWidgetSize(QSize(300, 400));

	init();
}

JYunApplication::~JYunApplication()
{
	if (m_pSetupButton)
		delete m_pSetupButton;
	m_pSetupButton = nullptr;

	if (m_pCloudDiskButton)
		delete m_pCloudDiskButton;
	m_pCloudDiskButton = nullptr;

	if (m_pBackupButton)
		delete m_pBackupButton;
	m_pBackupButton = nullptr;
}

void JYunApplication::initWidget()
{
	m_pSetupButton = new QPushButton(this);
	m_pSetupButton->setObjectName("app_setup");
	m_pSetupButton->resize(100, 100);
	m_pSetupButton->move(100, 30);
	m_pSetupButton->setToolTip("设置");

	//////////////////////////////////////////
	//////////////测试使用///////////////////
	/////////////////////////////////////////
	//设置头像
	setAvatar(QPixmap("head.png"));
	/////////////////////////////////////////
	/////////////////////////////////////////


	m_pCloudDiskButton = new QPushButton("网络云盘", this);
	m_pCloudDiskButton->setObjectName("app_button");
	m_pCloudDiskButton->resize(180, 45);
	m_pCloudDiskButton->move(60, 200);

	m_pBackupButton = new QPushButton("数据备份", this);
	m_pBackupButton->setObjectName("app_button");
	m_pBackupButton->resize(180, 45);
	m_pBackupButton->move(60, 280);
}

void JYunApplication::conn()
{
	//设置按钮信号槽绑定
	connect(m_pSetupButton, &QPushButton::clicked, this, &JYunApplication::startJYunSetup);

	//网络云盘按钮信号槽绑定
	connect(m_pCloudDiskButton, &QPushButton::clicked, this, &JYunApplication::startJYunCloudDisk);

	//数据备份按钮信号槽绑定
	connect(m_pBackupButton, &QPushButton::clicked, this, &JYunApplication::startJYunBackup);
}

void JYunApplication::initData()
{
}

void JYunApplication::init()
{
	initWidget();

	conn();

	initData();
}

void JYunApplication::resizeEvent(QResizeEvent * e)
{
	paintRoundRect();

	BasicWidget::resizeEvent(e);
}

void JYunApplication::setAvatar(const QPixmap & pixmap)
{
	QIcon icon(pixmap);

	m_pSetupButton->setIcon(icon);
	m_pSetupButton->setIconSize(m_pSetupButton->size());
}

void JYunApplication::closeEvent(QCloseEvent * e)
{
	//弹去确认框
	// 1. 注销
	// 2. 最小化
	// 3. 退出
	ApplicationCloseDialog::Type type = \
		ApplicationCloseDialog::waitForAnswer();
	
	switch (type) {
	case ApplicationCloseDialog::Type::Close:
		e->ignore();
		break;
	case ApplicationCloseDialog::Type::Logout:
		break;
	case ApplicationCloseDialog::Type::Hide:
		break;
	case ApplicationCloseDialog::Type::Quit:
		break;
	default:
		e->ignore();
		break;
	}
}

void JYunApplication::startJYunSetup()
{

}

void JYunApplication::startJYunCloudDisk()
{
}

void JYunApplication::startJYunBackup()
{
}
