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
#include <QtWidgets/QApplication>

#include "JYunStart.h"

#include "widget/JYunLogin.h"
#include "exception/Exception.h"
#include "logic/Security.h"
#include "widget/JYunSerious.h"

#include "widget\JYunApplication.h"
#include "widget\JYunCloudDisk.h"
#include "widget\JYunSetup.h"
#include "logic\file\FileObject.h"
#include "logic\GlobalParameter.h"
#include "logic\network\JYunTcp.h"
#include "logic\JYunConfig.h"
#include "logic\User.h"

void finish();

int main(int argc, char *argv[])
{
	//注册一个清理函数
	atexit(finish);

	QApplication a(argc, argv);

	//JYunStart::start();

	//安全检查
	//初始化全局变量
	//获取配置文件 =====
	//读取配置文件
	//建立网络
	//启动客户端


	Security security;
	GlobalParameter *param = GlobalParameter::getInstance();
	JYunLogin w;
	JYunSerious recall;
	try {
		security.check();

		param->setConfig(new JYunConfig);
		param->setTcpNetwork(new JYunTcp);
		param->setUser(new User());
		w.showWidget();

		//w.show();
	}
	catch (Exception e) {
		recall.show();
	}
	
	return a.exec();
}

/*********************************************
* 所有任务结束之后做清理工作
**********************************************
*/
void finish()
{
	GlobalParameter::destroyInstance();
}