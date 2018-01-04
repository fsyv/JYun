#include "stdafx.h"
#include "CloudDiskFileWidget.h"


CloudDiskFileWidget::CloudDiskFileWidget(QWidget *parent):
	QFrame(parent)
{
	resize(700, 450);

	initWidget();
}


CloudDiskFileWidget::~CloudDiskFileWidget()
{
}

void CloudDiskFileWidget::initWidget()
{
	setObjectName("clouddisk_file");
}
