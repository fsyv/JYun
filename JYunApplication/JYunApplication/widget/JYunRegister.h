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
* @brief : ע�����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/30
**/

#include "basic\BasicWidget.h"

class JYunRegister : public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunRegister();
	~JYunRegister();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	void checkUsername(RegisteredMsg::RegisteredResult result);
	void registeredUser(RegisteredMsg::RegisteredResult result);

	//�û���������ʧȥ����
	void usernameInputFocusOut();

	void resizeEvent(QResizeEvent *e) override;
	bool eventFilter(QObject *object, QEvent *e) override;

protected slots:
	//ע�ᰴť�ۺ���
	void registered();
	//ע����
	void registeredResult(RegisteredMsg *rmsg);

private:
	QLineEdit *m_pUsernameLabel;
	QLineEdit *m_pUsernameLineEdit;
	QLineEdit *m_pUserpassLabel;
	QLineEdit *m_pUserpassLineEdit;
	QPushButton *m_pRegisterButton;
};

