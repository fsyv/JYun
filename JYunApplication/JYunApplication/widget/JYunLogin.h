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

protected:
	void init();
	//界面初始化
	void initWidget();
	//绑定信号与槽
	void conn();
	//初始化数据
	void initData();

	//重写父类resizeEvent
	void resizeEvent(QResizeEvent *e) override;

protected slots:
    //记住密码按钮响应函数
    void rememberPass(bool checked);
	//自动登录按钮响应函数
	void autoLogin(bool checked);
    //登录按钮的响应函数
    void login(bool checked);

private:
	QComboBox *m_pUsernameInput;
	QLineEdit *m_pUserpassInput;
	QCheckBox *m_pRememberPass;
	QCheckBox *m_pAutoLogin;
	QPushButton *m_pLoginButton;
};

