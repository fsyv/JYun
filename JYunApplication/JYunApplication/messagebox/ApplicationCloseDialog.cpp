#include "stdafx.h"
#include "ApplicationCloseDialog.h"


ApplicationCloseDialog::ApplicationCloseDialog():
	m_eType(Type::Close),
	m_pCloseButton(nullptr),
	m_pText(nullptr),
	m_pLogoutButton(nullptr),
	m_pHideButton(nullptr),
	m_pQuitButton(nullptr)
{
	changeWidgetSize(QSize(300, 100));

	init();
}


ApplicationCloseDialog::~ApplicationCloseDialog()
{
	if (m_pCloseButton)
		delete m_pCloseButton;
	m_pCloseButton = nullptr;

	if (m_pText)
		delete m_pText;
	m_pText = nullptr;

	if (m_pLogoutButton)
		delete m_pLogoutButton;
	m_pLogoutButton = nullptr;

	if (m_pHideButton)
		delete m_pHideButton;
	m_pHideButton = nullptr;

	if (m_pQuitButton)
		delete m_pQuitButton;
	m_pQuitButton = nullptr;
}

ApplicationCloseDialog::Type ApplicationCloseDialog::getType()
{
	return m_eType;
}

ApplicationCloseDialog::Type ApplicationCloseDialog::waitForAnswer()
{
	ApplicationCloseDialog dialog;
	dialog.show();
	dialog.exec();

	return dialog.getType();;
}

void ApplicationCloseDialog::initWidget()
{
	m_pCloseButton = new QPushButton(this);
	m_pCloseButton->setObjectName("application_close_dialog_close");
	m_pCloseButton->resize(32, 32);
	m_pCloseButton->move(width() - m_pCloseButton->width(), 0);
	m_pCloseButton->setIcon(QIcon(":/resource/button/close.png"));
	m_pCloseButton->setIconSize(m_pCloseButton->size());
	m_pCloseButton->setToolTip("关闭");

	m_pText = new QLabel("确定退出?", this);
	m_pText->setObjectName("application_close_dialog_text");
	m_pText->move(0, 28);
	m_pText->resize(300, 28);
	m_pText->setAlignment(Qt::AlignCenter);
	m_pText->setFont(QFont("方正舒体", 10));

	m_pLogoutButton = new QPushButton("注销", this);
	m_pLogoutButton->setObjectName("application_close_dialog_logout");
	m_pLogoutButton->move(15, 60);
	m_pLogoutButton->resize(80, 30);

	m_pHideButton = new QPushButton("最小化", this);
	m_pHideButton->setObjectName("application_close_dialog_hide");
	m_pHideButton->move(110, 60);
	m_pHideButton->resize(80, 30);

	m_pQuitButton = new QPushButton("退出", this);
	m_pQuitButton->setObjectName("application_close_dialog_quit");
	m_pQuitButton->move(205, 60);
	m_pQuitButton->resize(80, 30);
}

void ApplicationCloseDialog::conn()
{
	connect(m_pCloseButton, &QPushButton::clicked, this, [this]() {
		m_eType = Type::Close;
		close();
	});

	connect(m_pLogoutButton, &QPushButton::clicked, this, [this]() {
		m_eType = Type::Logout;
		close();
	});

	connect(m_pHideButton, &QPushButton::clicked, this, [this]() {
		m_eType = Type::Hide;
		close();
	});

	connect(m_pQuitButton, &QPushButton::clicked, this, [this]() {
		m_eType = Type::Quit;
		close();
	});
}

void ApplicationCloseDialog::init()
{
	initWidget();

	conn();
}
