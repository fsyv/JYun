#pragma execution_character_set("utf-8")

#include "stdafx.h"
#include "widget/JYunApplication.h"
#include "widget/JYunLogin.h"
#include "widget/JYunSetup.h"
#include "widget/JYunCloudDisk.h"
#include "widget/JYunBackup.h"
#include "messagebox/JYunMessageBox.h"

#include "exception/Exception.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	JYunMessageBox::prompt("buyao");

	//try {
	//	w.show();
	//}
	//catch (Exception e) {
	//	int b = 0;
	//}
	
	return a.exec();
}
