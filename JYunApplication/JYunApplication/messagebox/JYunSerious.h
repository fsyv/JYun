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
* @brief : ÌáÊ¾¿ò
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/5
**/

#include "basic\BasicWidget.h"
class JYunSerious : public BasicWidget
{
public:
	JYunSerious();
	~JYunSerious();
protected:
	void initWidget();

	void resizeEvent(QResizeEvent *e) override;

private:
	QLabel *m_pPicture;
	QLabel *m_pText;
	QLineEdit *m_pContactLabel;
	QLineEdit *m_pContactInput;
	QPlainTextEdit *m_pPlainTextEdit;
	QPushButton *m_pCommit;
	QPushButton *m_pCancel;
};

