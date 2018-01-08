#include "stdafx.h"
#include "JYunLogin.h"

#include "database/Database.h"

JYunLogin::JYunLogin() :
	m_pUsernameInput(nullptr),
	m_pUserpassInput(nullptr),
	m_pRememberPass(nullptr),
	m_pAutoLogin(nullptr),
	m_pLoginButton(nullptr)
{
	changeWidgetSize(QSize(300, 400));
	
	init();
}


JYunLogin::~JYunLogin()
{
	if(m_pUsernameInput)
		delete m_pUsernameInput;
	m_pUsernameInput = nullptr;

	if (m_pUserpassInput)
		delete m_pUserpassInput;
	m_pUserpassInput = nullptr;

	if (m_pRememberPass)
		delete m_pRememberPass;
	m_pRememberPass = nullptr;

	if (m_pAutoLogin)
		delete m_pAutoLogin;
	m_pAutoLogin = nullptr;

	if (m_pLoginButton)
		delete m_pLoginButton;
	m_pLoginButton = nullptr;
}

void JYunLogin::init()
{
	initWidget();

	conn();

	initData();
}

/***************************************************
*�����ʼ��
****************************************************
*/
void JYunLogin::initWidget()
{
	m_pUsernameInput = new QComboBox(this);
	m_pUsernameInput->setObjectName("login_username");
	m_pUsernameInput->resize(180, 30);
	m_pUsernameInput->move(60, 150);
	m_pUsernameInput->setEditable(true);
	m_pUsernameInput->lineEdit()->setPlaceholderText(" �������ʺ�");

	m_pUserpassInput = new QLineEdit(this);
	m_pUserpassInput->setObjectName("login_userpass");
	m_pUserpassInput->resize(180, 30);
	m_pUserpassInput->move(60, 180);
	m_pUserpassInput->setPlaceholderText(" ����������");
	m_pUserpassInput->setEchoMode(QLineEdit::Password);

	m_pRememberPass = new QCheckBox("��ס����", this);
	m_pRememberPass->setObjectName("login_checkbox");
	m_pRememberPass->resize(90, 30);
	m_pRememberPass->move(60, 250);

	m_pAutoLogin = new QCheckBox("�Զ���¼", this);
	m_pAutoLogin->setObjectName("login_checkbox");
	m_pAutoLogin->resize(90, 30);
	m_pAutoLogin->move(150, 250);

	m_pLoginButton = new QPushButton("��  ¼", this);
	m_pLoginButton->setObjectName("login_button");
	m_pLoginButton->resize(180, 30);
	m_pLoginButton->move(60, 300);
}

/***************************************************
*���ź����
****************************************************
*/
void JYunLogin::conn()
{
	//�û����������¼���
	connect(m_pUsernameInput->lineEdit(), &QLineEdit::textChanged, m_pUserpassInput, &QLineEdit::clear);

	//��ס���밴ť�¼���
	connect(m_pRememberPass, &QCheckBox::clicked, this, &JYunLogin::rememberPass);

	//�Զ���¼��ť�¼���
	connect(m_pAutoLogin, &QCheckBox::clicked, this, &JYunLogin::autoLogin);

	//��¼��ť�¼���
	connect(m_pLoginButton, &QPushButton::clicked, this, &JYunLogin::login);
}

/***************************************************
*��ʼ������
****************************************************
*/
void JYunLogin::initData()
{
	Database db;

	QStringList users = db.getUserLists();
	m_pUsernameInput->addItems(users);

	//��ȡ�Զ���¼״̬
	bool autoLogin = db.isAutoLogin();
	if (autoLogin)
	{
		m_pAutoLogin->setDown(true);
		login(true);
	}
}

/***************************************************
*��д����resizeEvent
*����Բ�Ǿ���
****************************************************
*/
void JYunLogin::resizeEvent(QResizeEvent * e)
{
	paintRoundRect();

	BasicWidget::resizeEvent(e);
}

/***************************************************
*��ס���밴ť��Ӧ����
****************************************************
*/
void JYunLogin::rememberPass(bool checked)
{

}

/***************************************************
*�Զ���¼��ť��Ӧ����
****************************************************
*/
void JYunLogin::autoLogin(bool checked)
{
}

/***************************************************
*��¼��ť����Ӧ����
****************************************************
*/
void JYunLogin::login(bool checked)
{

}
