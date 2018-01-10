#include "stdafx.h"
#include "JYunLogin.h"

#include "database/Database.h"
#include "messagebox/JYunMessageBox.h"
#include "messagebox/LoginMessageBox.h"

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
*界面初始化
****************************************************
*/
void JYunLogin::initWidget()
{
	m_pUsernameInput = new QComboBox(this);
	m_pUsernameInput->setObjectName("login_username");
	m_pUsernameInput->resize(180, 30);
	m_pUsernameInput->move(60, 150);
	m_pUsernameInput->setEditable(true);
	m_pUsernameInput->lineEdit()->setPlaceholderText(" 请输入帐号");

	m_pUserpassInput = new QLineEdit(this);
	m_pUserpassInput->setObjectName("login_userpass");
	m_pUserpassInput->resize(180, 30);
	m_pUserpassInput->move(60, 180);
	m_pUserpassInput->setPlaceholderText(" 请输入密码");
	m_pUserpassInput->setEchoMode(QLineEdit::Password);
	m_pUserpassInput->installEventFilter(this);

	m_pRememberPass = new QCheckBox("记住密码", this);
	m_pRememberPass->setObjectName("login_checkbox");
	m_pRememberPass->resize(90, 30);
	m_pRememberPass->move(60, 250);

	m_pAutoLogin = new QCheckBox("自动登录", this);
	m_pAutoLogin->setObjectName("login_checkbox");
	m_pAutoLogin->resize(90, 30);
	m_pAutoLogin->move(150, 250);

	m_pLoginButton = new QPushButton("登  录", this);
	m_pLoginButton->setObjectName("login_button");
	m_pLoginButton->resize(180, 30);
	m_pLoginButton->move(60, 300);
}

/***************************************************
*绑定信号与槽
****************************************************
*/
void JYunLogin::conn()
{
	//用户名输入栏事件绑定
	connect(m_pUsernameInput->lineEdit(), &QLineEdit::textChanged, m_pUserpassInput, &QLineEdit::clear);

	//密码输入栏事件绑定

	////记住密码按钮事件绑定
	//connect(m_pRememberPass, &QCheckBox::clicked, this, &JYunLogin::rememberPass);

	////自动登录按钮事件绑定
	//connect(m_pAutoLogin, &QCheckBox::clicked, this, &JYunLogin::autoLogin);

	//登录按钮事件绑定
	connect(m_pLoginButton, &QPushButton::clicked, this, &JYunLogin::login);
}

/***************************************************
*初始化数据
****************************************************
*/
void JYunLogin::initData()
{
	m_stFakePass = QString("不要偷看密码哦!");

	Database db;

	QStringList users = db.getUserLists();
	m_pUsernameInput->addItems(users);

	QString username = m_pUsernameInput->lineEdit()->text();
	
	if (!username.isEmpty())
	{
		//获取自动登录状态
		bool autoLogin = db.isAutoLogin(username);
		//获取是否记住密码
		bool rememberPass = db.isRememberPass(username);

		setRemberPass(rememberPass);
		setAutoLogin(autoLogin);

		if (autoLogin)
			login();
	}
}

/***************************************************
*设置记住密码按钮状态
****************************************************
*/
void JYunLogin::setRemberPass(bool status)
{
	m_pRememberPass->setDown(status);

	if (status)
		m_pUserpassInput->setText(m_stFakePass);
}

/***************************************************
*设置自动登录按钮就状态
****************************************************
*/
void JYunLogin::setAutoLogin(bool status)
{
	m_pAutoLogin->setDown(status);
}

/***************************************************
*保存密码
****************************************************
*/
void JYunLogin::keepUserpass(QString username, QString userpass)
{
	Database db;
	db.setUsernamepass(username, userpass);
}

/***************************************************
*用户配置
****************************************************
*/
void JYunLogin::userConfig()
{
	{
		Database db;
		//获取是否记住密码
		db.setRememberPass(m_pUsernameInput->lineEdit()->text(), m_pRememberPass->isChecked());
		//获取自动登录状态
		db.setAutoLogin(m_pUsernameInput->lineEdit()->text(), m_pAutoLogin->isChecked());
	}

	//如果要记住密码，保存到本地数据库
	if (m_pRememberPass->isChecked())
		keepUserpass(m_pUsernameInput->lineEdit()->text(), m_pUserpassInput->text());
	else
		keepUserpass(m_pUsernameInput->lineEdit()->text());
}

/***************************************************
*登录成功
****************************************************
*/
void JYunLogin::loginSuccess()
{
	//保存用户配置
	userConfig();
}

/***************************************************
*登录失败
****************************************************
*/
void JYunLogin::loginFailed()
{
}

/***************************************************
*密码输入栏得到焦点
****************************************************
*/
void JYunLogin::passInputFocusIn()
{
	m_pUserpassInput->setText(m_stRealPass);
}

/***************************************************
*密码输入栏失去焦点
****************************************************
*/
void JYunLogin::passInputFocusOut()
{
	m_stRealPass = m_pUserpassInput->text();
	m_pUserpassInput->setText(m_stFakePass);
}

/***************************************************
*重写父类resizeEvent
*绘制圆角矩形
****************************************************
*/
void JYunLogin::resizeEvent(QResizeEvent * e)
{
	paintRoundRect();

	BasicWidget::resizeEvent(e);
}

/***************************************************
*重写父类事件过滤器
*捕抓密码输入栏得到焦点和失去焦点事件
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

	return BasicWidget::eventFilter(object, e);
}

/***************************************************
*记住密码按钮响应函数
****************************************************
*/
void JYunLogin::rememberPass(bool checked)
{

}

/***************************************************
*自动登录按钮响应函数
****************************************************
*/
void JYunLogin::autoLogin(bool checked)
{
	//Database db;
	//db.setAutoLogin(checked);
}

/***************************************************
*登录按钮的响应函数
****************************************************
*/
void JYunLogin::login()
{
	//if (m_pUsernameInput->lineEdit()->text().isEmpty() ||
	//	m_pUserpassInput->text().isEmpty())
	//{
	//	JYunMessageBox::prompt(QString("请输入帐号或者密码!"));
	//	return;
	//}

	//弹出一个窗口
	//倒计时6秒
	//窗口返回结果
	//如果没有取消则发送登录请求
	bool ret = LoginMessageBox::waitForConfirm(3000);
}
