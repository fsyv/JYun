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
* @brief : …Ë÷√ΩÁ√Ê
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/1
**/

#include "basic/BasicWidget.h"
class JYunSetup : public BasicWidget
{
public:
	explicit JYunSetup();
	~JYunSetup();

protected:
	void initWidget();

	void resizeEvent(QResizeEvent *e) override;

private:

	QPushButton *m_pChangeAvatarButton;
	QLineEdit *m_pUsernameLabel;
	QLineEdit *m_pUsernameLineEdit;
	QLineEdit *m_pUserpassLabel;
	QLineEdit *m_pUserpassLineEdit;
	QPushButton *m_pCommitButton;
};

