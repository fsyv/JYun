#include "stdafx.h"
#include "JYunLogin.h"

#include "database/Database.h"
#include "messagebox/JYunMessageBox.h"
#include "messagebox/LoginMessageBox.h"
#include "logic/network/JYunHttp.h"
#include "logic/JYunTools.h"

#include "widget/JYunApplication.h"

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

/***************************************************
*������ʾ
****************************************************
*/
void JYunLogin::show()
{
	BasicWidget::show();

	//500���������û�����ִ�ж�ʱ��
	QTimer::singleShot(500, this, [this]() {
		if (m_pAutoLogin->isChecked())
			login();
	});
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
	m_pUsernameInput->installEventFilter(this);

	m_pUserpassInput = new QLineEdit(this);
	m_pUserpassInput->setObjectName("login_userpass");
	m_pUserpassInput->resize(180, 30);
	m_pUserpassInput->move(60, 180);
	m_pUserpassInput->setPlaceholderText(" ����������");
	m_pUserpassInput->setEchoMode(QLineEdit::Password);
	m_pUserpassInput->installEventFilter(this);

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
	connect(m_pUsernameInput->lineEdit(), &QLineEdit::textChanged, this, &JYunLogin::usernameInputChange);
	connect(m_pUsernameInput->lineEdit(), &QLineEdit::returnPressed, this, &JYunLogin::usernameReturnPressed);
	connect(m_pUsernameInput, SIGNAL(currentIndexChanged(QString)), this, SLOT(usernameInputIndexChanged(QString)));

	//�����������¼���
	connect(m_pUserpassInput, &QLineEdit::returnPressed, this, &JYunLogin::userpassReturnPressed);

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
	m_stFakePass = QString("��Ҫ͵������Ŷ!");

	Database db;

	QStringList users = db.getUserLists();
	if (users.isEmpty())
		return;

	m_pUsernameInput->addItems(users);

	getUserConfigByUsername(m_pUsernameInput->lineEdit()->text());
}

/***************************************************
*���ü�ס���밴ť״̬
****************************************************
*/
void JYunLogin::setRemberPass(bool status)
{
	m_pRememberPass->setChecked(status);
	if (status)
		m_pUserpassInput->setText(m_stFakePass);
}

/***************************************************
*�����Զ���¼��ť��״̬
****************************************************
*/
void JYunLogin::setAutoLogin(bool status)
{
	m_pAutoLogin->setChecked(status);
}

/***************************************************
*��������
****************************************************
*/
void JYunLogin::keepUserpass(QString username, QString userpass)
{
	Database db;
	db.setUsernamepass(username, userpass);
}

/***************************************************
*�ù��û�����ȡ�û�����
****************************************************
*/
void JYunLogin::getUserConfigByUsername(QString username)
{
	Database db;
	//��ȡ�Զ���¼״̬
	bool autoLogin = db.isAutoLogin(username);
	//��ȡ�Ƿ��ס����
	bool rememberPass = db.isRememberPass(username);

	setRemberPass(rememberPass);
	setAutoLogin(autoLogin);
	m_stRealPass = db.getPassByUsername(username);
}

/***************************************************
*�û�����
****************************************************
*/
void JYunLogin::userConfig()
{
	{
		Database db;
		//��ȡ�Ƿ��ס����
		//��ȡ�Զ���¼״̬
		db.setLoginConfig(m_pUsernameInput->lineEdit()->text(), 
			m_pRememberPass->isChecked(), 
			m_pAutoLogin->isChecked()
		);
	}

	//���Ҫ��ס���룬���浽�������ݿ�
	if (m_pRememberPass->isChecked())
		keepUserpass(m_pUsernameInput->lineEdit()->text(), m_stRealPass);
	else
		keepUserpass(m_pUsernameInput->lineEdit()->text());
}

/***************************************************
*����������
****************************************************
*/
void JYunLogin::startJYunApplication()
{
	hide();
	JYunApplication *w = new JYunApplication(m_pUsernameInput->lineEdit()->text());
	w->show();
}

/***************************************************
*��¼�ɹ�
****************************************************
*/
void JYunLogin::loginSuccess()
{
	//�����û�����
	userConfig();

	//����������
	startJYunApplication();
}

/***************************************************
*��¼ʧ��
****************************************************
*/
void JYunLogin::loginFailed()
{
}

/***************************************************
*�û���������ʧȥ����
****************************************************
*/
void JYunLogin::usernameInputFocuOut()
{
	getUserConfigByUsername(m_pUsernameInput->lineEdit()->text());
}

/***************************************************
*�����������õ�����
****************************************************
*/
void JYunLogin::passInputFocusIn()
{
	m_pUserpassInput->setText(m_stRealPass);
}

/***************************************************
*����������ʧȥ����
****************************************************
*/
void JYunLogin::passInputFocusOut()
{
	m_stRealPass = m_pUserpassInput->text();
	m_pUserpassInput->setText(m_stFakePass);
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
*��д�����¼�������
*��ץ�����������õ������ʧȥ�����¼�
****************************************************
*/
bool JYunLogin::eventFilter(QObject * object, QEvent * e)
{
	if (object == m_pUserpassInput)
	{
		if (e->type() == QEvent::FocusIn)
			passInputFocusIn();
		else if (e->type() == QEvent::FocusOut)
			passInputFocusOut();
	}
	else if (object == m_pUsernameInput)
	{
		if (e->type() == QEvent::FocusOut)
			usernameInputFocuOut();
	}

	return BasicWidget::eventFilter(object, e);
}

/***************************************************
*�û����������ı���Ӧ����
****************************************************
*/
void JYunLogin::usernameInputChange()
{
	m_pUserpassInput->clear();
	m_stRealPass.clear();
	m_pRememberPass->setChecked(false);
	m_pAutoLogin->setChecked(false);
}

/***************************************************
*�û����������س������¼���Ӧ����
****************************************************
*/
void JYunLogin::usernameReturnPressed()
{
	if (m_stRealPass.isEmpty() || m_pUserpassInput->text().isEmpty())
		m_pUserpassInput->setFocus();
}

/***************************************************
*�û��������������ı���Ӧ����
****************************************************
*/
void JYunLogin::usernameInputIndexChanged(QString username)
{
	getUserConfigByUsername(username);
}

/***************************************************
*�û������������س������¼���Ӧ����
****************************************************
*/
void JYunLogin::userpassReturnPressed()
{
	if (!m_pUserpassInput->text().isEmpty())
	{
		passInputFocusOut();
		login();
	}
}

/***************************************************
*�Զ���¼��ť��Ӧ����
****************************************************
*/
void JYunLogin::autoLogin(bool checked)
{
	if (checked)
		m_pRememberPass->setChecked(checked);
}

/***************************************************
*��¼��ť����Ӧ����
****************************************************
*/
void JYunLogin::login()
{
	//if (m_pUsernameInput->lineEdit()->text().isEmpty() ||
	//	m_pUserpassInput->text().isEmpty())
	//{
	//	JYunMessageBox::prompt(QString("�������ʺŻ�������!"));
	//	return;
	//}

	//����һ������
	//����ʱ6��
	//���ڷ��ؽ��
	//���û��ȡ�����͵�¼����
	bool ret = LoginMessageBox::waitForConfirm(3000);

	if (!ret)
		return;

	QString username = m_pUsernameInput->lineEdit()->text();

	JYunHttp http;
	QMap<QString, QString>  result = http.login(username, m_stRealPass);

	//////////////////////////////////////////
	//////////////����ʹ��///////////////////
	/////////////////////////////////////////
	result["login_result"] = QString("True");
	/////////////////////////////////////////
	/////////////////////////////////////////

	if (result.value("login_result") == QString("True"))
	{
		//��¼�ɹ�
		loginSuccess();
	}
	else
	{
		//��¼ʧ��
		JYunMessageBox::prompt(result.value("login_error"));
		loginFailed();
	}
}
