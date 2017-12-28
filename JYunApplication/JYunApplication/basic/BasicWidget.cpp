#include "stdafx.h"
#include "BasicWidget.h"

#include "exception\Exception.h"
#include "CloseButton.h"

BasicWidget::BasicWidget(QWidget *parent):
	QWidget(parent),
	m_pCloseButton(nullptr)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setStyleSheetFromFile(":/resource/qss/BasicWidget.qss");

	//内存不足抛出异常
	try {
		m_pCloseButton = new CloseButton(this);
	}
	catch (const std::bad_alloc &e) {
		throw Exception(QString("内存不足"));
	}

	connect(m_pCloseButton, &CloseButton::click, this, &BasicWidget::closeWidget);

	initWidget();
	//setMouseTracking(true);
}


BasicWidget::~BasicWidget()
{
	if (m_pCloseButton)
		delete m_pCloseButton;
	m_pCloseButton = nullptr;
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
	moveWidget(e->globalPos());

	QWidget::mouseMoveEvent(e);
}

void BasicWidget::mousePressEvent(QMouseEvent * e)
{
	setCursor(QCursor(Qt::OpenHandCursor));

	m_mousePressPoint = e->pos();

	QWidget::mousePressEvent(e);
}

void BasicWidget::mouseReleaseEvent(QMouseEvent * e)
{
	unsetCursor();

	QWidget::mouseReleaseEvent(e);
}

void BasicWidget::paintEvent(QPaintEvent * e)
{

}

void BasicWidget::resizeEvent(QResizeEvent * e)
{
	initWidget();

	//QPainterPath path;

	//QRectF rect = QRectF(0, 0, width(), height());

	//path.addRoundRect(rect, 50, 50);

	//QPolygon polygon = path.toFillPolygon().toPolygon();//获得这个路径上的所有的点       
	//QRegion region(polygon);//根据这个点构造这个区域 
	//setMask(region);

	QWidget::resizeEvent(e);
}

void BasicWidget::initWidget()
{
	m_pCloseButton->move(width() - m_pCloseButton->width(), 0);
}

void BasicWidget::moveWidget(const QPoint &point)
{
	move(point - m_mousePressPoint);
}

void BasicWidget::changeWidgetSize()
{
}

void BasicWidget::closeWidget()
{
	QWidget::close();
}


