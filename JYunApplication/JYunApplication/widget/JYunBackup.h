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
* @brief : 数据备份界面
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/5
**/

#include "basic/BasicWidget.h"

class BackupLeftWidget;
class BackupFileListWidget;

class JYunBackup : public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunBackup();
	~JYunBackup();

protected:
	void initWidget();
private:
	QLabel *m_pTitle;
	BackupLeftWidget *m_pLeftWidget;
	BackupFileListWidget *m_pFileListWidget;
};

