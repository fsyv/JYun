#include "stdafx.h"
#include "JYunApplication.h"

#include "messagebox/ApplicationCloseDialog.h"

#include "widget/JYunSetup.h"
#include "widget/JYunCloudDisk.h"
#include "widget/JYunBackup.h"
#include "logic/User.h"
#include "logic/file/ImageFile.h"
#include "logic/network/JYunTcp.h"

JYunApplication::JYunApplication() :
	m_pSetupButton(nullptr),
	m_pCloudDiskButton(nullptr),
	m_pBackupButton(nullptr),
	m_pSystemTrayIcon(nullptr),
	m_pHeadImage(nullptr)
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

	if (m_pHeadImage)
		delete m_pHeadImage;
	m_pHeadImage = nullptr;
}

void JYunApplication::initWidget()
{
	m_pSetupButton = new QPushButton(this);
	m_pSetupButton->setObjectName("app_setup");
	m_pSetupButton->resize(100, 100);
	m_pSetupButton->move(100, 30);
	m_pSetupButton->setToolTip("����");

	m_pCloudDiskButton = new QPushButton("��������", this);
	m_pCloudDiskButton->setObjectName("app_button");
	m_pCloudDiskButton->resize(180, 45);
	m_pCloudDiskButton->move(60, 200);

	m_pBackupButton = new QPushButton("���ݱ���", this);
	m_pBackupButton->setObjectName("app_button");
	m_pBackupButton->resize(180, 45);
	m_pBackupButton->move(60, 280);

	//ϵͳ���̳�ʼ��
	m_pSystemTrayIcon = new QSystemTrayIcon(QIcon(":/resource/logo/tray_logo.ico"), this);
	m_pSystemTrayIcon->setToolTip("JYunApplication");
	m_pSystemTrayIcon->show();
	//�Ҽ��˵�
	QMenu *systemTrayMenu = new QMenu();
	//�Ҽ��˵�-���������̰�ť��ʼ��
	QAction *openCloudDiskAct = new QAction("����������");
	connect(openCloudDiskAct, &QAction::triggered, this, &JYunApplication::startJYunCloudDisk);
	systemTrayMenu->addAction(openCloudDiskAct);
	//�Ҽ��˵�-�����ݱ��ݰ�ť��ʼ��
	QAction *openBackupAct = new QAction("�����ݱ���");
	connect(openBackupAct, &QAction::triggered, this, &JYunApplication::startJYunBackup);
	systemTrayMenu->addAction(openBackupAct);
	//����һ���ָ���
	systemTrayMenu->addSeparator();
	//�Ҽ��˵�-�˳���ť��ʼ��
	QAction *quitAct = new QAction("�˳�");
	connect(quitAct, &QAction::triggered, this, &JYunApplication::close);
	systemTrayMenu->addAction(quitAct);
	m_pSystemTrayIcon->setContextMenu(systemTrayMenu);
}

void JYunApplication::conn()
{
	//���ð�ť�źŲ۰�
	connect(m_pSetupButton, &QPushButton::clicked, this, &JYunApplication::startJYunSetup);

	//�������̰�ť�źŲ۰�
	connect(m_pCloudDiskButton, &QPushButton::clicked, this, &JYunApplication::startJYunCloudDisk);

	//���ݱ��ݰ�ť�źŲ۰�
	connect(m_pBackupButton, &QPushButton::clicked, this, &JYunApplication::startJYunBackup);

	//���̵���źŲ۰�
	connect(m_pSystemTrayIcon, &QSystemTrayIcon::activated, this, &JYunApplication::taryClick);

	//ע�������¼���
	JYunTcp *network = GlobalParameter::getInstance()->getTcpNetwork();
	connect(network, &JYunTcp::getUserHeadMd5Msg, this, &JYunApplication::updateHead);
}

void JYunApplication::initData()
{
	m_pHeadImage = new ImageFile;

	getUserAvatar();
}

void JYunApplication::init()
{
	initWidget();

	conn();

	initData();
}

/***************************************************
*������ʾ��ʱ��رմ���
****************************************************
*/
void JYunApplication::closeWidgetWhenShown(QCloseEvent * e)
{
	//��ȥȷ�Ͽ�
	// 1. ע��
	// 2. ��С��
	// 3. �˳�
	ApplicationCloseDialog::Type type = \
		ApplicationCloseDialog::waitForAnswer();

	switch (type) {
	case ApplicationCloseDialog::Type::Close:
		e->ignore();
		break;
	case ApplicationCloseDialog::Type::Logout:
		emit logout();
		break;
	case ApplicationCloseDialog::Type::Hide:
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
*��ȡ�û�ͷ��
****************************************************
*/
void JYunApplication::getUserAvatar()
{
	JYunTcp *network = GlobalParameter::getInstance()->getTcpNetwork();
	User *user = GlobalParameter::getInstance()->getUser();

	network->sendGetUserHeadMd5Msg(user->getUsername());
}

void JYunApplication::closeEvent(QCloseEvent * e)
{
	if (isVisible())
		closeWidgetWhenShown(e);
	else
		BasicWidget::closeEvent(e);
}

/***************************************************
*�������ý���
****************************************************
*/
void JYunApplication::startJYunSetup()
{
	hide();

	JYunSetup w;
	w.setHeadMd5(m_pHeadImage->fileName());
	w.show();

	QEventLoop event_loop;
	connect(&w, &JYunCloudDisk::quitWidget, &event_loop, &QEventLoop::quit);
	event_loop.exec();

	show();
}

/***************************************************
*�����������̽���
****************************************************
*/
void JYunApplication::startJYunCloudDisk()
{
	hide();

	JYunCloudDisk w;
	w.show();

	QEventLoop event_loop;
	connect(&w, &JYunCloudDisk::quitWidget, &event_loop, &QEventLoop::quit);
	event_loop.exec();

	show();
}

/***************************************************
*�������ݱ��ݽ���
****************************************************
*/
void JYunApplication::startJYunBackup()
{
	hide();

	JYunBackup w;
	w.show();

	QEventLoop event_loop;
	connect(&w, &JYunCloudDisk::quitWidget, &event_loop, &QEventLoop::quit);
	event_loop.exec();

	show();
}

/***************************************************
*���̵����Ӧ����
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

void JYunApplication::updateHead(GetUserHeadMd5 * gmsg)
{
	if (!gmsg)
		return;

	QString md5 = gmsg->m_aMd5;

	m_pHeadImage->setMd5(md5);

	QString headPath = QDir::currentPath() + QString("/head/") + md5;
	m_pHeadImage->setLocalUrl(headPath);

	QFileInfo fileinfo(headPath);
	if (fileinfo.exists())
		setAvatar(QPixmap(headPath));
	else
	{
		m_pHeadImage->getRemoteUrl();
		m_pHeadImage->download();

		connect(m_pHeadImage, &ImageFile::finished, this, [this]() {
			QString head = QDir::currentPath() + "/head/" + m_pHeadImage->fileName();
			setAvatar(QPixmap(head));
		});
	}
}
