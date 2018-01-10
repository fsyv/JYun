#include "stdafx.h"
#include "BasicMessageBox.h"


BasicMessageBox::BasicMessageBox(QWidget *parent):
	QDialog(parent),
	m_pCloseButton(nullptr),
	m_bMousePress(false)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setStyleSheetFromFile(":/resource/qss/BasicMessageBox.qss");
}


BasicMessageBox::~BasicMessageBox()
{
}

void BasicMessageBox::setStyleSheetFromFile(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
		setStyleSheet(file.readAll());
	file.close();
}

void BasicMessageBox::mouseMoveEvent(QMouseEvent * e)
{
	if (m_bMousePress)
		moveWidget(e->globalPos());

	QWidget::mouseMoveEvent(e);
}

void BasicMessageBox::mousePressEvent(QMouseEvent * e)
{
	m_bMousePress = true;

	setCursor(QCursor(Qt::OpenHandCursor));

	m_mousePressPoint = e->pos();

	QWidget::mousePressEvent(e);
}

void BasicMessageBox::mouseReleaseEvent(QMouseEvent * e)
{
	m_bMousePress = false;

	unsetCursor();

	QWidget::mouseReleaseEvent(e);
}

void BasicMessageBox::moveWidget(const QPoint &point)
{
	move(point - m_mousePressPoint);
}

void BasicMessageBox::changeWidgetSize(const QSize &size)
{
	resize(size);
}

void BasicMessageBox::paintRoundRect(const int &radius)
{
	QPainterPath path;

	QRectF rect = QRectF(0, 0, width(), height());

	path.addRoundRect(rect, radius, radius);

	QPolygon polygon = path.toFillPolygon().toPolygon();//获得这个路径上的所有的点       
	QRegion region(polygon);//根据这个点构造这个区域 
	setMask(region);
}
