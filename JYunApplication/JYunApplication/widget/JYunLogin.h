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
* @brief : µÇÂ¼½çÃæ
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
	void initWidget();

	void resizeEvent(QResizeEvent *e) override;

private:
	QComboBox *m_pUsernameInput;
	QLineEdit *m_pUserpassInput;
	QCheckBox *m_pRememberPass;
	QCheckBox *m_pAutoLogin;
	QPushButton *m_pLoginButton;
};

