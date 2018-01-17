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
* @brief : �������ݿ�
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/8
**/

#include <QSqlDatabase>

class Database
{
public:
	Database();
	~Database();

	//���õ�¼ʱ���û�����
	void setLoginConfig(QString username, bool rememberpass, bool autologin);
	//�����û�������
	void setUsernamepass(QString username, QString userpass);

	//�ӱ������ݿ��ȡ�û��б�
	QStringList getUserLists();
	//�ӱ������ݿ��ȡ�Ƿ��Զ���¼
	bool isAutoLogin(QString username);
	//�ӱ������ݿ��ȡ�Ƿ��ס����
	bool isRememberPass(QString username);
	//�ӱ������ݿ�ͨ���ʺŻ�ȡ����
	QString getPassByUsername(QString username);
private:
	QSqlDatabase db;
};
