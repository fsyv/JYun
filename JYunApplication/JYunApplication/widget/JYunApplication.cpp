#include "stdafx.h"
#include "JYunApplication.h"

#include "messagebox/ApplicationCloseDialog.h"

#include "logic/network/JYunHttp.h"

#include "widget/JYunSetup.h"
#include "widget/JYunCloudDisk.h"
#include "widget/JYunBackup.h"

JYunApplication::JYunApplication(QString username):
	m_pSetupButton(nullptr),
	m_pCloudDiskButton(nullptr),
	m_pBackupButton(nullptr),
	m_pSystemTrayIcon(nullptr),
	m_stUsername(username)
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

	if (m_pSystemTrayIcon)
		delete m_pSystemTrayIcon;
	m_pSystemTrayIcon = nullptr;
}

void JYunApplication::initWidget()
{
	m_pSetupButton = new QPushButton(this);
	m_pSetupButton->setObjectName("app_setup");
	m_pSetupButton->resize(100, 100);
	m_pSetupButton->move(100, 30);
	m_pSetupButton->setToolTip("设置");

	m_pCloudDiskButton = new QPushButton("网络云盘", this);
	m_pCloudDiskButton->setObjectName("app_button");
	m_pCloudDiskButton->resize(180, 45);
	m_pCloudDiskButton->move(60, 200);

	m_pBackupButton = new QPushButton("数据备份", this);
	m_pBackupButton->setObjectName("app_button");
	m_pBackupButton->resize(180, 45);
	m_pBackupButton->move(60, 280);

	//系统托盘初始化
	m_pSystemTrayIcon = new QSystemTrayIcon(QIcon(":/resource/logo/tray_logo.ico"), this);
	m_pSystemTrayIcon->setToolTip("JYunApplication");
	m_pSystemTrayIcon->show();
	//右键菜单
	QMenu *systemTrayMenu = new QMenu();
	//右键菜单-打开网络云盘按钮初始化
	QAction *openCloudDiskAct = new QAction("打开网络云盘");
	connect(openCloudDiskAct, &QAction::triggered, this, &JYunApplication::startJYunCloudDisk);
	systemTrayMenu->addAction(openCloudDiskAct);
	//右键菜单-打开数据备份按钮初始化
	QAction *openBackupAct = new QAction("打开数据备份");
	connect(openBackupAct, &QAction::triggered, this, &JYunApplication::startJYunBackup);
	systemTrayMenu->addAction(openBackupAct);
	//增加一个分割线
	systemTrayMenu->addSeparator();
	//右键菜单-退出按钮初始化
	QAction *quitAct = new QAction("退出");
	connect(quitAct, &QAction::triggered, this, &JYunApplication::close);
	systemTrayMenu->addAction(quitAct);
	m_pSystemTrayIcon->setContextMenu(systemTrayMenu);
}

void JYunApplication::conn()
{
	//设置按钮信号槽绑定
	connect(m_pSetupButton, &QPushButton::clicked, this, &JYunApplication::startJYunSetup);

	//网络云盘按钮信号槽绑定
	connect(m_pCloudDiskButton, &QPushButton::clicked, this, &JYunApplication::startJYunCloudDisk);

	//数据备份按钮信号槽绑定
	connect(m_pBackupButton, &QPushButton::clicked, this, &JYunApplication::startJYunBackup);

	//托盘点击信号槽绑定
	connect(m_pSystemTrayIcon, &QSystemTrayIcon::activated, this, &JYunApplication::taryClick);
}

void JYunApplication::initData()
{
	getUserAvatar();
}

void JYunApplication::init()
{
	initWidget();

	conn();

	initData();
}

/***************************************************
*界面显示的时候关闭窗口
****************************************************
*/
void JYunApplication::closeWidgetWhenShown(QCloseEvent * e)
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
		//hide();
		BasicWidget::hide();
		e->ignore();
		break;
	case ApplicationCloseDialog::Type::Quit:
		break;
	default:
		e->ignore();
		break;
	}
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

/***************************************************
*获取用户头像
****************************************************
*/
void JYunApplication::getUserAvatar()
{
	QString headPath = QDir::currentPath() + QString("/head/") + m_stUsername;
	QFile head(headPath);
	if (head.exists())
		setAvatar(QPixmap(headPath));
	else
	{
		JYunHttp http;
		http.getHead();
		setAvatar(QPixmap(headPath));
	}
}

void JYunApplication::closeEvent(QCloseEvent * e)
{
	if (isVisible())
		closeWidgetWhenShown(e);
	else
		BasicWidget::closeEvent(e);
}

/***************************************************
*启动设置界面
****************************************************
*/
void JYunApplication::startJYunSetup()
{
	hide();

	JYunSetup *w = new JYunSetup;
	w->show();
}

/***************************************************
*启动网络云盘界面
****************************************************
*/
void JYunApplication::startJYunCloudDisk()
{
	hide();

	JYunCloudDisk *w = new JYunCloudDisk;
	w->show();
}

/***************************************************
*启动数据备份界面
****************************************************
*/
void JYunApplication::startJYunBackup()
{
	hide();

	JYunBackup *w = new JYunBackup;
	w->show();
}

/***************************************************
*托盘点击响应函数
****************************************************
*/
void JYunApplication::taryClick(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Unknown:
		break;
	case QSystemTrayIcon::Context:
		break;
	case QSystemTrayIcon::DoubleClick:
		show();
		break;
	case QSystemTrayIcon::Trigger:
		show();
		break;
	case QSystemTrayIcon::MiddleClick:
		show();
		break;
	default:
		break;
	}
}
