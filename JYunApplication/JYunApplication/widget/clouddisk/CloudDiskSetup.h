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
* @brief : Õ¯¬Á‘∆≈Ã…Ë÷√ΩÁ√Ê
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/25
**/

#include <QWidget>

class CloudDiskSetup : public QFrame
{
	Q_OBJECT
public:
	explicit CloudDiskSetup(QWidget *parent = nullptr);
	~CloudDiskSetup();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

protected slots:
	void clicked();

private:
	QLineEdit *m_label;
	QLineEdit *m_line;
	QPushButton *m_button;
};

