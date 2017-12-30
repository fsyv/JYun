#include "stdafx.h"
#include "JYunLogin.h"


JYunLogin::JYunLogin() :
	m_pUsernameInput(nullptr),
	m_pUserpassInput(nullptr),
	m_pRememberPass(nullptr),
	m_pAutoLogin(nullptr),
	m_pLoginButton(nullptr)
{
	changeWidgetSize(QSize(300, 400));
	
	initWidget();
}


JYunLogin::~JYunLogin()
{
}

void JYunLogin::initWidget()
{
	m_pUsernameInput = new QComboBox(this);
	m_pUsernameInput->setObjectName("login_username");
	m_pUsernameInput->resize(180, 30);
	m_pUsernameInput->move(60, 150);
	m_pUsernameInput->setEditable(true);
	m_pUsernameInput->lineEdit()->setPlaceholderText(" ÇëÊäÈëÕÊºÅ");

	m_pUserpassInput = new QLineEdit(this);
	m_pUserpassInput->setObjectName("login_userpass");
	m_pUserpassInput->resize(180, 30);
	m_pUserpassInput->move(60, 180);
	m_pUserpassInput->setPlaceholderText(" ÇëÊäÈëÃÜÂë");
	m_pUserpassInput->setEchoMode(QLineEdit::Password);

	m_pRememberPass = new QCheckBox("¼Ç×¡ÃÜÂë", this);
	m_pRememberPass->setObjectName("login_checkbox");
	m_pRememberPass->resize(90, 30);
	m_pRememberPass->move(60, 250);

	m_pAutoLogin = new QCheckBox("×Ô¶¯µÇÂ¼", this);
	m_pAutoLogin->setObjectName("login_checkbox");
	m_pAutoLogin->resize(90, 30);
	m_pAutoLogin->move(150, 250);

	m_pLoginButton = new QPushButton("µÇ  Â¼", this);
	m_pLoginButton->setObjectName("login_button");
	m_pLoginButton->resize(180, 30);
	m_pLoginButton->move(60, 300);

	//m_pUsernameInput->setStyleSheet("border: 1px solid gray;border-radius: 3px;");
	//m_pUserpassInput->setStyleSheet("background:#ffffff;color:gray;text-align:center;border-radius:15; font:15px");

}

void JYunLogin::resizeEvent(QResizeEvent * e)
{
	paintRoundRect();

	BasicWidget::resizeEvent(e);
}
