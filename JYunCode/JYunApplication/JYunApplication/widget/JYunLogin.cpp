#include "stdafx.h"
#include "JYunLogin.h"

#include "logic/GlobalParameter.h"

#include "database/Database.h"
#include "messagebox/JYunMessageBox.h"
#include "messagebox/LoginMessageBox.h"
#include "logic/JYunTools.h"

#include "widget/JYunApplication.h"
#include "widget/JYunRegister.h"

#include "logic/User.h"

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
*界面显示
****************************************************
*/
void JYunLogin::showWidget()
{
	BasicWidget::show();

	//500毫秒后根据用户配置执行定时器
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
	m_pUsernameInput->installEventFilter(this);

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
	m_pLoginButton->resize(100, 30);
	m_pLoginButton->move(60, 300);

	m_pRegisterButton = new QPushButton("注册", this);
	m_pRegisterButton->setObjectName("login_button");
	m_pRegisterButton->resize(60, 30);
	m_pRegisterButton->move(180, 300);
}

/***************************************************
*绑定信号与槽
****************************************************
*/
void JYunLogin::conn()
{
	//用户名输入栏事件绑定
	connect(m_pUsernameInput->lineEdit(), &QLineEdit::textChanged, this, &JYunLogin::usernameInputChange);
	connect(m_pUsernameInput->lineEdit(), &QLineEdit::returnPressed, this, &JYunLogin::usernameReturnPressed);
	connect(m_pUsernameInput, SIGNAL(currentIndexChanged(QString)), this, SLOT(usernameInputIndexChanged(QString)));

	//密码输入栏事件绑定
	connect(m_pUserpassInput, &QLineEdit::returnPressed, this, &JYunLogin::userpassReturnPressed);

	//自动登录按钮事件绑定
	connect(m_pAutoLogin, &QCheckBox::clicked, this, &JYunLogin::autoLogin);

	//登录按钮事件绑定
	connect(m_pLoginButton, &QPushButton::clicked, this, &JYunLogin::login);

	//注册按钮事件绑定
	connect(m_pRegisterButton, &QPushButton::clicked, this, &JYunLogin::registered);
}

/***************************************************
*初始化数据
****************************************************
*/
void JYunLogin::initData()
{
	m_stFakePass = QString("不要偷看密码哦!");

	{
		Database db;

		QStringList users = db.getUserLists();

		if (users.isEmpty())
			return;

		m_pUsernameInput->addItems(users);
	}

	getUserConfigByUsername(m_pUsernameInput->lineEdit()->text());

	if (m_pRememberPass->isChecked())
	{
		Database db;

		m_stPassMd5 = db.getPassByUsername(m_pUsernameInput->lineEdit()->text());
	}
	    
}

/***************************************************
*设置记住密码按钮状态
****************************************************
*/
void JYunLogin::setRemberPass(bool status)
{
	m_pRememberPass->setChecked(status);
	if (status)
		m_pUserpassInput->setText(m_stFakePass);
}

/***************************************************
*设置自动登录按钮就状态
****************************************************
*/
void JYunLogin::setAutoLogin(bool status)
{
	m_pAutoLogin->setChecked(status);
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
*通过用户名获取用户配置
****************************************************
*/
void JYunLogin::getUserConfigByUsername(QString username)
{
	Database db;
	//获取自动登录状态
	bool autoLogin = db.isAutoLogin(username);
	//获取是否记住密码
	bool rememberPass = db.isRememberPass(username);

	setRemberPass(rememberPass);
	setAutoLogin(autoLogin);
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
		//获取自动登录状态
		db.setLoginConfig(m_pUsernameInput->lineEdit()->text(), 
			m_pRememberPass->isChecked(), 
			m_pAutoLogin->isChecked()
		);
	}

	//如果要记住密码，保存到本地数据库
	if (m_pRememberPass->isChecked())
		keepUserpass(m_pUsernameInput->lineEdit()->text(), m_stPassMd5);
	else
		keepUserpass(m_pUsernameInput->lineEdit()->text());
}

/***************************************************
*主程序启动
****************************************************
*/
void JYunLogin::startJYunApplication()
{
	hide();

	JYunApplication w(m_pUsernameInput->lineEdit()->text());
	w.show();

	QEventLoop event_loop;
	connect(&w, &JYunApplication::logout, &event_loop, &QEventLoop::quit);
	connect(&w, &JYunApplication::logout, this, &JYunLogin::show);
	event_loop.exec();

}

/***************************************************
*登录成功
****************************************************
*/
void JYunLogin::loginSuccess()
{
	//设置全局用户变量
	User *user = GlobalParameter::getInstance()->getUser();
	QString username = m_pUsernameInput->lineEdit()->text();
	user->setUsername(username);

	//保存用户配置
	userConfig();

	//启动主程序
	startJYunApplication();
}

/***************************************************
*登录失败
****************************************************
*/
void JYunLogin::loginFailed()
{
}

/***************************************************
*用户名输入栏失去焦点
****************************************************
*/
void JYunLogin::usernameInputFocuOut()
{
	getUserConfigByUsername(m_pUsernameInput->lineEdit()->text());
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
	if (!m_stRealPass.isEmpty())
	{
		m_stPassMd5 = JYunTools::stringMD5(m_stRealPass);
		m_pUserpassInput->setText(m_stFakePass);
	}
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
	else if (object == m_pUsernameInput)
	{
		if (e->type() == QEvent::FocusOut)
			usernameInputFocuOut();
	}

	return BasicWidget::eventFilter(object, e);
}

/***************************************************
*用户名输入栏改变响应函数
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
*用户名输入栏回车按下事件响应函数
****************************************************
*/
void JYunLogin::usernameReturnPressed()
{
	if (m_stRealPass.isEmpty() || m_pUserpassInput->text().isEmpty())
		m_pUserpassInput->setFocus();
}

/***************************************************
*用户名下拉框索引改变响应函数
****************************************************
*/
void JYunLogin::usernameInputIndexChanged(QString username)
{
	getUserConfigByUsername(username);
}

/***************************************************
*用户密码输入栏回车按下事件响应函数
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
*自动登录按钮响应函数
****************************************************
*/
void JYunLogin::autoLogin(bool checked)
{
	if (checked)
		m_pRememberPass->setChecked(checked);
}

/***************************************************
*登录按钮的响应函数
****************************************************
*/
void JYunLogin::login()
{
	if (m_pUsernameInput->lineEdit()->text().isEmpty() ||
		m_pUserpassInput->text().isEmpty())
	{
		JYunMessageBox::prompt(QString("请输入帐号或者密码!"));
		return;
	}

	//弹出一个窗口
	//倒计时3秒
	//窗口返回结果
	//如果没有取消则发送登录请求
	bool ret = LoginMessageBox::waitForConfirm(3000);

	if (!ret)
		return;

	QString username = m_pUsernameInput->lineEdit()->text();
	QString userpass = m_stPassMd5;

	//JYunHttp http;
	//QMap<QString, QString> result = http.login(username, userpass);

	//if (result.value("login_result") == QString("True"))
	//{
	//	//登录成功
	//	loginSuccess();
	//}
	//else
	//{
	//	//登录失败
	//	JYunMessageBox::prompt(result.value("login_error"));
	//	loginFailed();
	//}
}

/***************************************************
*注册按钮响应函数
****************************************************
*/
void JYunLogin::registered()
{
	hide();

	JYunRegister w;
	w.show();
	QEventLoop temp_loop;
	connect(&w, &JYunRegister::quitWidget, &temp_loop, &QEventLoop::quit);
	temp_loop.exec();

	show();
}
