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
* @brief : ��¼����
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
	//�����ʼ��
	void initWidget();
	//���ź����
	void conn();
	//��ʼ������
	void initData();
	//���ü�ס���밴ť״̬
	void setRemberPass(bool status);
	//�����Զ���¼��ť��״̬
	void setAutoLogin(bool status);
	//��������
	void keepUserpass(QString username, QString userpass = QString());
	//�û�����
	void userConfig();
	//��¼�ɹ�
	void loginSuccess();
	//��¼ʧ��
	void loginFailed();
	//�����������õ�����
	void passInputFocusIn();
	//����������ʧȥ����
	void passInputFocusOut();

	//��д����resizeEvent
	void resizeEvent(QResizeEvent *e) override;
	//��д�����¼�������
	bool eventFilter(QObject *object, QEvent *e) override;

protected slots:
    //��ס���밴ť��Ӧ����
    void rememberPass(bool checked);
	//�Զ���¼��ť��Ӧ����
	void autoLogin(bool checked);
    //��¼��ť����Ӧ����
    void login();


private:
	QComboBox *m_pUsernameInput;
	QLineEdit *m_pUserpassInput;
	QCheckBox *m_pRememberPass;
	QCheckBox *m_pAutoLogin;
	QPushButton *m_pLoginButton;

	//������
	QString m_stFakePass;
	//������
	QString m_stRealPass;
};

