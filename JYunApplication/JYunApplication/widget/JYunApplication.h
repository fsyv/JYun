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
* @brief : �����棨����ѡ��
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2017/12/31
**/

#include "basic/BasicWidget.h"

class ImageFile;

class JYunApplication : public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunApplication();
	~JYunApplication();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();
	//������ʾ��ʱ��رմ���
	void closeWidgetWhenShown(QCloseEvent *e);

	void resizeEvent(QResizeEvent *e) override;
	void setAvatar(const  QPixmap &pixmap);
	//��ȡ�û�ͷ��
	void getUserAvatar();
	//����ͷ��
	void downloadHead();

	void closeEvent(QCloseEvent *e) override;

public slots:
    //�������ý���
    void startJYunSetup();
	//�����������̽���
	void startJYunCloudDisk();
	//�������ݱ��ݽ���
	void startJYunBackup();
	//���̵����Ӧ����
	void taryClick(QSystemTrayIcon::ActivationReason reason);
	//����ͷ����Ӧ����
	void updateHead(GetUserHead *gmsg);

signals:
	void logout();

private:
	QPushButton *m_pSetupButton;
	QPushButton *m_pCloudDiskButton;
	QPushButton *m_pBackupButton;

	//����
	QSystemTrayIcon *m_pSystemTrayIcon;

	//ͷ���ļ�
	ImageFile *m_pHeadImage;
};
