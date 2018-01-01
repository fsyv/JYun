#pragma execution_character_set("utf-8")

#include "stdafx.h"
#include "widget/JYunApplication.h"
#include "widget/JYunLogin.h"
#include "widget/JYunSetup.h"
#include "exception/Exception.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	JYunSetup w;

	try {
		w.show();
	}
	catch (Exception e) {
		int b = 0;
	}
	
	return a.exec();
}
