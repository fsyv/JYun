#include "stdafx.h"
#include "TaskListChild.h"

TaskListChild::TaskListChild(QWidget *parent): 
	QWidget(parent, Qt::FramelessWindowHint), 
	currentValue(0),
	userdVaule(100)
{
	init();
}

TaskListChild::~TaskListChild()
{
    currentValue = 0;

	delete m_pButton;
	delete m_pName;
}

void TaskListChild::init()
{
	resize(120, 120);
	setAutoFillBackground(false);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(0xFF, 0xFF, 0xFF, 0xFF));
	setPalette(pal);

	m_pButton = new QPushButton(this);
	m_pButton->setObjectName("tasklist_button");
	m_pButton->move(44, 43);
	m_pButton->resize(35, 35);
	m_pButton->setCheckable(true);
	connect(m_pButton, &QPushButton::clicked, this, [this](bool b) {
		emit clicked(b);
	});

	m_pName = new QLabel(this);
	m_pName->move(35, 100);
	m_pName->resize(80, 20);

	setStyleSheetFromFile(":/resource/qss/progressbar.qss");
}

void TaskListChild::setLabelName(QString name)
{
	m_pName->setText(name);
	setToolTip(name);
}

void TaskListChild::setStyleSheetFromFile(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
		setStyleSheet(file.readAll());
	file.close();
}

void TaskListChild::loadProgress(qint64 current, qint64 total)
{
    currentValue = current * 100 / total;
    update();
}

void TaskListChild::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor usedColor(165, 220, 62);
    QColor freeColor(215, 215, 215);
    painter.drawPixmap(QRect((width() - backGround.width())/2 , (height() - backGround.height())/2, backGround.width(), backGround.height()) , backGround);

    painter.translate(width() / 2, height() / 2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.save();
    painter.rotate(42);
    painter.setPen(QPen(usedColor, 2));
    for (int i = 0; i < currentValue ; ++i) {
        painter.drawLine(0, 50, 0, 60);
        painter.rotate(2.8);
    }
    painter.setPen(QPen(freeColor, 3));
    for (int i = currentValue; i < 100 ; ++i) {
        painter.drawLine(0, 50, 0, 60);
        painter.rotate(2.8);
    }

    painter.translate(-width()/2, -height()/2);
    painter.setBrush(QColor(233, 233, 233));
    painter.setPen(QPen(QColor(233, 233, 233), 15));
    painter.drawEllipse(QRectF((width()/2 - 40), (height()/2 - 40), 80, 80));

    QConicalGradient conicalGradient(width()/2, height()/2, 360 * currentValue / 100.0);
    conicalGradient.setColorAt(0, QColor(45, 204, 112));
    conicalGradient.setColorAt(1.0, QColor(51, 152, 219));
    painter.setPen(QPen(QBrush(conicalGradient), 30));
    painter.drawEllipse(QRectF((width()/2 - 23), (height()/2 - 23), 46, 46));

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(249, 249, 249));
    painter.drawEllipse(QRectF((width()/2 - 25), (height()/2 - 25), 50, 50));
}

