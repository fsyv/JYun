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
* @brief : Õ¯¬Á‘∆≈Ã÷˜ΩÁ√Ê
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/1
**/

#include "basic\BasicWidget.h"

class CloudDiskTopWidget;
class CloudDiskLeftWidget;
class CloudDiskStatusBar;
class CloudDiskFileWidget;
class CloudDiskSetup;
class CloudDiskTaskList;

class JYunCloudDisk : public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunCloudDisk(const QString &username);
	~JYunCloudDisk();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

private:
	QLabel *m_pTitle;
	CloudDiskTopWidget *m_pTopWidget;
	CloudDiskLeftWidget *m_pLeftWidget;
	CloudDiskStatusBar *m_pStatusBar;
	CloudDiskFileWidget *m_pFileWidget;
	CloudDiskSetup *m_pSetup;
	CloudDiskTaskList *m_pTaskList;

	QString m_stUsername;
};

