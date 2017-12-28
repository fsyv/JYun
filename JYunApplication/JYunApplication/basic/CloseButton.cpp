#include "stdafx.h"
#include "CloseButton.h"

CloseButton::CloseButton(QWidget * parent) :
	QLabel(parent),
	m_bFlat(false)
{
	setPixmap(QPixmap(":/resource/button/close.png"));
	resize(32, 32);
	
	setScaledContents(true);
}

CloseButton::~CloseButton()
{

}

void CloseButton::mouseMoveEvent(QMouseEvent * e)
{
	if (e->x() < width() && e->x() >= 0 && e->y() < height() && e->y() >= 0)
		m_bFlat = true;
	else
		m_bFlat = false;

	e->accept();
}

void CloseButton::mousePressEvent(QMouseEvent * e)
{
	m_bFlat = true;
	
	e->accept();
}

void CloseButton::mouseReleaseEvent(QMouseEvent * e)
{
	if (m_bFlat)
		emit click();

	m_bFlat = false;

	e->accept();
}

void CloseButton::enterEvent(QEvent * e)
{
	setStyleSheet("QLabel { background-color: red; };");

	QLabel::enterEvent(e);
}

void CloseButton::leaveEvent(QEvent * e)
{
	setStyleSheet("QLabel { background-color: transparent; };");

	QLabel::leaveEvent(e);
}
