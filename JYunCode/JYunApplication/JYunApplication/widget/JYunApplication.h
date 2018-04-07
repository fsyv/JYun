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
* @brief : 主界面（功能选择）
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2017/12/31
**/

#include "basic/BasicWidget.h"

class JYunApplication : public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunApplication(QString username);
	~JYunApplication();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();
	//界面显示的时候关闭窗口
	void closeWidgetWhenShown(QCloseEvent *e);

	void resizeEvent(QResizeEvent *e) override;
	void setAvatar(const  QPixmap &pixmap);
	//获取用户头像
	void getUserAvatar();

	void closeEvent(QCloseEvent *e) override;

public slots:
    //启动设置界面
    void startJYunSetup();
	//启动网络云盘界面
	void startJYunCloudDisk();
	//启动数据备份界面
	void startJYunBackup();
	//托盘点击响应函数
	void taryClick(QSystemTrayIcon::ActivationReason reason);

signals:
	void logout();

private:
	QPushButton *m_pSetupButton;
	QPushButton *m_pCloudDiskButton;
	QPushButton *m_pBackupButton;

	//托盘
	QSystemTrayIcon *m_pSystemTrayIcon;
	//用户名
	QString m_stUsername;
};
