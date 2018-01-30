#pragma once
#pragma execution_character_set("utf-8")

/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 登录界面
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2017/12/30
**/

#include "basic/BasicWidget.h"

class JYunLogin : public BasicWidget{
	Q_OBJECT
public:
	explicit JYunLogin();
	~JYunLogin();

	//界面显示
	void showWidget();

protected:
	void init();
	//界面初始化
	void initWidget();
	//绑定信号与槽
	void conn();
	//初始化数据
	void initData();
	//设置记住密码按钮状态
	void setRemberPass(bool status);
	//设置自动登录按钮就状态
	void setAutoLogin(bool status);
	//保存密码
	void keepUserpass(QString username, QString userpass = QString());
	//用过用户名获取用户配置
	void getUserConfigByUsername(QString username);
	//用户配置
	void userConfig();
	//主程序启动
	void startJYunApplication();
	//登录成功
	void loginSuccess();
	//登录失败
	void loginFailed();
	//用户名输入栏失去焦点
	void usernameInputFocuOut();
	//密码输入栏得到焦点
	void passInputFocusIn();
	//密码输入栏失去焦点
	void passInputFocusOut();

	//重写父类resizeEvent
	void resizeEvent(QResizeEvent *e) override;
	//重写父类事件过滤器
	bool eventFilter(QObject *object, QEvent *e) override;

protected slots:
    //用户名输入栏改变响应函数
    void usernameInputChange();
	//用户名输入栏回车按下事件响应函数
	void usernameReturnPressed();
	//用户名下拉框索引改变响应函数
	void usernameInputIndexChanged(QString username);
	//用户密码输入栏回车按下事件响应函数
	void userpassReturnPressed();
	//自动登录按钮响应函数
	void autoLogin(bool checked);
    //登录按钮的响应函数
    void login();
	//注册按钮响应函数
	void registered();

private:
	QComboBox *m_pUsernameInput;
	QLineEdit *m_pUserpassInput;
	QCheckBox *m_pRememberPass;
	QCheckBox *m_pAutoLogin;
	QPushButton *m_pLoginButton;
	QPushButton *m_pRegisterButton;

	//假密码
	QString m_stFakePass;
	//真密码
	QString m_stRealPass;
	//密码md5
	QString m_stPassMd5;
};

