#include "stdafx.h"
#include "BasicWidget.h"

#include "exception\Exception.h"
#include "CloseButton.h"

BasicWidget::BasicWidget(QWidget *parent) :
	QWidget(parent),
	m_pCloseButton(nullptr),
	m_bMousePress(false)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setStyleSheetFromFile(":/resource/qss/style.qss");

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
	if (m_bMousePress)
		moveWidget(e->globalPos());

	QWidget::mouseMoveEvent(e);
}

void BasicWidget::mousePressEvent(QMouseEvent * e)
{
	m_bMousePress = true;

	setCursor(QCursor(Qt::OpenHandCursor));

	m_mousePressPoint = e->pos();

	QWidget::mousePressEvent(e);
}

void BasicWidget::mouseReleaseEvent(QMouseEvent * e)
{
	m_bMousePress = false;

	unsetCursor();

	QWidget::mouseReleaseEvent(e);
}

void BasicWidget::paintEvent(QPaintEvent * e)
{
	QWidget::paintEvent(e);
}

void BasicWidget::resizeEvent(QResizeEvent * e)
{
	initWidget();

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

void BasicWidget::changeWidgetSize(const QSize &size)
{
	resize(size);
}

void BasicWidget::paintRoundRect(const int &radius)
{
	QPainterPath path;

	QRectF rect = QRectF(0, 0, width(), height());

	path.addRoundRect(rect, radius, radius);

	QPolygon polygon = path.toFillPolygon().toPolygon();//获得这个路径上的所有的点       
	QRegion region(polygon);//根据这个点构造这个区域 
	setMask(region);
}

void BasicWidget::closeWidget()
{
	QWidget::close();
}


