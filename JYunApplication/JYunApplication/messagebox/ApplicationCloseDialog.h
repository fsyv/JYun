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
* @brief : application界面退出按钮按下提示框
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/18
**/

#include "basic\BasicMessageBox.h"

class ApplicationCloseDialog : public BasicMessageBox
{
	Q_OBJECT
public:
	enum class Type {
		Close = 0,		//关闭对话框
		Logout,			//注销
		Hide,			//最小化
		Quit			//退出
	};
public:
	ApplicationCloseDialog();
	~ApplicationCloseDialog();

	Type getType();

	static Type waitForAnswer();

protected:
	void initWidget();
	void conn();

	void init();

private:
	Type m_eType;
	QPushButton * m_pCloseButton;

	QLabel * m_pText;

	QPushButton *m_pLogoutButton;
	QPushButton *m_pHideButton;
	QPushButton *m_pQuitButton;
};

