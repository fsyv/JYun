#include "stdafx.h"
#include "CloudDiskStatusBarChildWidget.h"


CloudDiskStatusBarChildWidget::CloudDiskStatusBarChildWidget(FolderRole role, QWidget *parent) :
	QFrame(parent),
	m_pNameLabel(nullptr),
	m_eRole(role)
{
	setStyleSheetFromFile(":/resource/qss/CloudDiskStatusBarChildWidget.qss");
	initData();
	initWidget();
}


CloudDiskStatusBarChildWidget::~CloudDiskStatusBarChildWidget()
{
	if (m_pNameLabel)
		delete m_pNameLabel;
	m_pNameLabel = nullptr;
}

void CloudDiskStatusBarChildWidget::setName(const QString & name)
{
	m_pNameLabel->setText(name);

	adjustLabelWidth();
	
	setToolTip(name);

	initPath();
}

void CloudDiskStatusBarChildWidget::setFolderRole(const FolderRole & name)
{
	m_eRole = name;

	initPath();
}

int CloudDiskStatusBarChildWidget::textWidth() const
{
	return m_iTextWidth;
}

void CloudDiskStatusBarChildWidget::initData()
{
	m_iRriangleHight = 28;
	m_iMaxTextWidth = 60;
	m_iMinTextWidth = 40;
}

void CloudDiskStatusBarChildWidget::initWidget()
{
	m_pNameLabel = new QLabel(this);

	if (m_eRole == FolderRole::Root)
		m_pNameLabel->move(5, 0);
	else
		m_pNameLabel->move(m_iRriangleHight + 5, 0);
	
	m_pNameLabel->setAlignment(Qt::AlignVCenter);
}

void CloudDiskStatusBarChildWidget::initRootPath()
{
	m_PainterPath = QPainterPath();
	m_PainterPath.moveTo(0, 0);
	m_PainterPath.lineTo(m_iTextWidth, 0);
	m_PainterPath.lineTo(m_iTextWidth + m_iRriangleHight, 20);
	m_PainterPath.lineTo(m_iTextWidth, 40);
	m_PainterPath.lineTo(0, 40);
	m_PainterPath.lineTo(0, 0);
	m_PainterPath.closeSubpath();
}

void CloudDiskStatusBarChildWidget::initOtherPath()
{
	m_PainterPath = QPainterPath();
	m_PainterPath.moveTo(0, 0);
	m_PainterPath.lineTo(m_iRriangleHight + m_iTextWidth, 0);
	m_PainterPath.lineTo(m_iRriangleHight + m_iTextWidth + m_iRriangleHight, 20);
	m_PainterPath.lineTo(m_iRriangleHight + m_iTextWidth, 40);
	m_PainterPath.lineTo(0, 40);
	m_PainterPath.lineTo(m_iRriangleHight, 20);
	m_PainterPath.lineTo(0, 0);
	m_PainterPath.closeSubpath();
}

void CloudDiskStatusBarChildWidget::initPath()
{
	if (m_eRole == FolderRole::Root)
		initRootPath();
	else
		initOtherPath();
}

void CloudDiskStatusBarChildWidget::adjustLabelWidth()
{
	m_pNameLabel->adjustSize();
	m_iTextWidth = m_pNameLabel->width();
	m_iTextWidth = m_iTextWidth < m_iMaxTextWidth ? m_iTextWidth : m_iMaxTextWidth;
	m_iTextWidth = m_iTextWidth > m_iMinTextWidth ? m_iTextWidth : m_iMinTextWidth;
	m_pNameLabel->resize(m_iTextWidth + 20, 40);

	QFontMetrics elideFont(m_pNameLabel->font());
	m_pNameLabel->setText(elideFont.elidedText(m_pNameLabel->text(), Qt::ElideRight, m_pNameLabel->width()));

	resize(m_iRriangleHight + m_iTextWidth + m_iRriangleHight, 40);
}

void CloudDiskStatusBarChildWidget::setStyleSheetFromFile(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
		setStyleSheet(file.readAll());
	file.close();
}

void CloudDiskStatusBarChildWidget::resizeEvent(QResizeEvent * e)
{
	QPolygon polygon = m_PainterPath.toFillPolygon().toPolygon();//获得这个路径上的所有的点
	QRegion region(polygon);//根据这个点构造这个区域 
	setMask(region);

	QFrame::resizeEvent(e);
}

void CloudDiskStatusBarChildWidget::paintEvent(QPaintEvent * e)
{
	QPainter painter(this);
	painter.setPen(QPen(QColor(150, 150, 150, 128)));
	painter.drawPath(m_PainterPath);

	QFrame::paintEvent(e);
}
