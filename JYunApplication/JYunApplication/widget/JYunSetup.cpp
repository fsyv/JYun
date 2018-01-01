#include "stdafx.h"
#include "JYunSetup.h"

JYunSetup::JYunSetup() :
	m_pChangeAvatarButton(nullptr),
	m_pUsernameLabel(nullptr),
	m_pUsernameLineEdit(nullptr),
	m_pUserpassLabel(nullptr),
	m_pUserpassLineEdit(nullptr),
	m_pCommitButton(nullptr)
{
	changeWidgetSize(QSize(300, 400));

	initWidget();
}


JYunSetup::~JYunSetup()
{
	if (m_pChangeAvatarButton)
		delete m_pChangeAvatarButton;
	m_pChangeAvatarButton = nullptr;

	if (m_pUsernameLabel)
		delete m_pUsernameLabel;
	m_pUsernameLabel = nullptr;

	if (m_pUsernameLineEdit)
		delete m_pUsernameLineEdit;
	m_pUsernameLineEdit = nullptr;

	if (m_pUserpassLabel)
		delete m_pUserpassLabel;
	m_pUserpassLabel = nullptr;

	if (m_pUserpassLineEdit)
		delete m_pUserpassLineEdit;
	m_pUserpassLineEdit = nullptr;

	if (m_pCommitButton)
		delete m_pCommitButton;
	m_pCommitButton = nullptr;
}

void JYunSetup::initWidget()
{
	m_pChangeAvatarButton = new QPushButton(this);
	m_pChangeAvatarButton->setObjectName("setup_change");
	m_pChangeAvatarButton->resize(100, 100);
	m_pChangeAvatarButton->move(100, 30);
	m_pChangeAvatarButton->setToolTip(QString("更换头像"));

	m_pUsernameLabel = new QLineEdit(" 帐号:", this);
	m_pUsernameLabel->setObjectName("setup_label");
	m_pUsernameLabel->resize(50, 30);
	m_pUsernameLabel->move(20, 200);
	m_pUsernameLabel->setDisabled(true);

	m_pUsernameLineEdit = new QLineEdit(this);
	m_pUsernameLineEdit->setObjectName("setup_input");
	m_pUsernameLineEdit->resize(210, 30);
	m_pUsernameLineEdit->move(70, 200);
	//帐号设置为不可编辑
	m_pUsernameLineEdit->setDisabled(true);
	//默认文字,编程使用
	m_pUsernameLineEdit->setText(QString("fsyv.me@gmail.com"));

	m_pUserpassLabel = new QLineEdit(" 密码:", this);
	m_pUserpassLabel->setObjectName("setup_label");
	m_pUserpassLabel->resize(50, 30);
	m_pUserpassLabel->move(20, 240);
	m_pUserpassLabel->setDisabled(true);

	m_pUserpassLineEdit = new QLineEdit(this);
	m_pUserpassLineEdit->setObjectName("setup_input");
	m_pUserpassLineEdit->resize(210, 30);
	m_pUserpassLineEdit->move(70, 240);
	m_pUserpassLineEdit->setEchoMode(QLineEdit::Password);
	m_pUserpassLineEdit->setPlaceholderText("请输入新的密码!");
	//默认文字,编程使用
	m_pUserpassLineEdit->setText(QString("fsyv.me@gmail.com"));

	m_pCommitButton = new QPushButton("提    交", this);
	m_pCommitButton->setObjectName("setup_commit");
	m_pCommitButton->resize(180, 30);
	m_pCommitButton->move(60, 320);
}

void JYunSetup::resizeEvent(QResizeEvent * e)
{
	paintRoundRect();

	BasicWidget::resizeEvent(e);
}
