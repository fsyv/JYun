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

	//������ʾ
	void showWidget();

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
	//�ù��û�����ȡ�û�����
	void getUserConfigByUsername(QString username);
	//�û�����
	void userConfig();
	//����������
	void startJYunApplication();
	//��¼�ɹ�
	void loginSuccess();
	//��¼ʧ��
	void loginFailed();
	//�û���������ʧȥ����
	void usernameInputFocuOut();
	//�����������õ�����
	void passInputFocusIn();
	//����������ʧȥ����
	void passInputFocusOut();

	//��д����resizeEvent
	void resizeEvent(QResizeEvent *e) override;
	//��д�����¼�������
	bool eventFilter(QObject *object, QEvent *e) override;

protected slots:
    //�û����������ı���Ӧ����
    void usernameInputChange();
	//�û����������س������¼���Ӧ����
	void usernameReturnPressed();
	//�û��������������ı���Ӧ����
	void usernameInputIndexChanged(QString username);
	//�û������������س������¼���Ӧ����
	void userpassReturnPressed();
	//�Զ���¼��ť��Ӧ����
	void autoLogin(bool checked);
    //��¼��ť����Ӧ����
    void login();
	//ע�ᰴť��Ӧ����
	void registered();

private:
	QComboBox *m_pUsernameInput;
	QLineEdit *m_pUserpassInput;
	QCheckBox *m_pRememberPass;
	QCheckBox *m_pAutoLogin;
	QPushButton *m_pLoginButton;
	QPushButton *m_pRegisterButton;

	//������
	QString m_stFakePass;
	//������
	QString m_stRealPass;
	//����md5
	QString m_stPassMd5;
};

