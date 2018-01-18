#pragma execution_character_set("utf-8")

/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2017/12/27
**/

#include "stdafx.h"

#include "widget/JYunLogin.h"
#include "exception/Exception.h"
#include "logic/Security.h"
#include "widget/JYunSerious.h"

#include <QtWidgets/QApplication>

#include "widget\JYunApplication.h"

void finish();

int main(int argc, char *argv[])
{
	//注册一个清理函数
	atexit(finish);

	QApplication a(argc, argv);

	JYunApplication w(QString("fsyv"));
	w.show();

	//Security security;
	//JYunLogin w;
	//JYunSerious recall;
	//try {
	//	security.check();
	//	w.show();
	//}
	//catch (Exception e) {
	//	recall.show();
	//}
	
	return a.exec();
}

/*********************************************
* 所有任务结束之后做清理工作
**********************************************
*/
void finish()
{
	
}