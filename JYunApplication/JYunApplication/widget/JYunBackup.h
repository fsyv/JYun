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

class QListWidget;
class QPushButton;

class JYunBackup : public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunBackup();
	~JYunBackup();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	void resizeEvent(QResizeEvent *e) override;

private:
	QListWidget *m_pListWidget;
	QPushButton *m_pSetup;

	QWidget *m_pWidget;

	//备份时间
	QLineEdit *m_label_date;
	QLineEdit *m_line_date;
	QPushButton *m_button_date;

	//备份目录
	QLineEdit *m_label_dir;
	QLineEdit *m_line_dir;
	QPushButton *m_button_dir;
};

