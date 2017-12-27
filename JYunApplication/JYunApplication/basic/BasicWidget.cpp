#include "stdafx.h"
#include "BasicWidget.h"


BasicWidget::BasicWidget(QWidget *parent):
	QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
	//setStyleSheetFromFile(":/JYunApplication/resource/qss/BasicWidget.qss");
	this->setStyleSheet("QWidget{ background-color: #1E90FF;}");
}


BasicWidget::~BasicWidget()
{
}

void BasicWidget::setStyleSheetFromFile(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
		setStyleSheet(file.readAll());
}

void BasicWidget::widgetStyle()
{
}

void BasicWidget::mouseMoveEvent(QMouseEvent * e)
{
}

void BasicWidget::mousePressEvent(QMouseEvent * e)
{
}

void BasicWidget::mouseReleaseEvent(QMouseEvent * e)
{
}

void BasicWidget::paintEvent(QPaintEvent * e)
{
}

void BasicWidget::resizeEvent(QResizeEvent * e)
{
}
