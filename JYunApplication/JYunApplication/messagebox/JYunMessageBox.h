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
* @brief : 提示框
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/5
**/

#include "basic\BasicWidget.h"

class JYunMessageBox : public BasicWidget
{
public:
	enum class Type {
		Prompt = 0,		//提示
		Success,		//成功
		Failed			//失败
	};
public:
	JYunMessageBox(const QString &string, const Type &type);
	~JYunMessageBox();

	static void prompt(const QString &string);
	static void success();
	static void failed();

protected:
	void initWidget();
	void setPicture();
	void resizeEvent(QResizeEvent *e) override;

private:
	QString m_stInfo;
	Type m_eType;

	QLabel *m_pPicture;
	QLabel *m_pText;
	QPushButton *m_pPushButton;
};

