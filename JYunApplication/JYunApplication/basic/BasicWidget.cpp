#include "stdafx.h"
#include "BasicWidget.h"

#include "exception\Exception.h"

BasicWidget::BasicWidget(QWidget *parent) :
	QWidget(parent),
	m_pCloseButton(nullptr),
	m_bMousePress(false)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setStyleSheetFromFile(":/resource/qss/style.qss");

	m_pCloseButton = new QPushButton(this);
	connect(m_pCloseButton, &QPushButton::clicked, this, &BasicWidget::closeWidget);

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
	file.close();
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
	m_pCloseButton->setObjectName("close");
	m_pCloseButton->resize(32, 32);
	m_pCloseButton->move(width() - m_pCloseButton->width(), 0);
	m_pCloseButton->setIcon(QIcon(":/resource/button/close.png"));
	m_pCloseButton->setIconSize(m_pCloseButton->size());
	m_pCloseButton->setToolTip("关闭");
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


