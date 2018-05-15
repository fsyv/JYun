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
* @brief : 设置界面
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/1
**/

#include "basic/BasicWidget.h"

class ImageFile;

class JYunSetup : public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunSetup();
	~JYunSetup();

	void setAvatar(const QPixmap &pixmap);
	void setHeadMd5(QString md5);

public slots:
    //更换头像按钮响应函数
    void changeHead();
	//提交按钮响应函数
	void commit();
	//修改
	void modify(ModifypassMsg *mmsg);

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	//密码输入栏得到焦点
	void passInputFocusIn();
	//密码输入栏失去焦点
	void passInputFocusOut();
	//从服务器获取数据更新头像
	void updateAvatar();

	void resizeEvent(QResizeEvent *e) override;
	bool eventFilter(QObject *object, QEvent *e) override;

private:
	QPushButton *m_pChangeAvatarButton;
	QLineEdit *m_pUsernameLabel;
	QLineEdit *m_pUsernameLineEdit;
	QLineEdit *m_pUserpassLabel;
	QLineEdit *m_pUserpassLineEdit;
	QPushButton *m_pCommitButton;

	QString m_stRealPass;
	QString m_stFakePass;
	QString m_strHeadMd5;

	ImageFile *m_pHeadImage;
};

