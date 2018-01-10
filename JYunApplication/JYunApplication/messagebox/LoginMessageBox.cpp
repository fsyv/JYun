#include "stdafx.h"
#include "LoginMessageBox.h"


LoginMessageBox::LoginMessageBox():
	m_bRet(true),
	m_iTimerID(0)
{
	changeWidgetSize(QSize(240, 150));
	setWindowModality(Qt::ApplicationModal);

	initWidget();
	conn();
}


LoginMessageBox::~LoginMessageBox()
{
	stopTimer();

	if (m_pPicture->movie())
		delete m_pPicture->movie();

	if (m_pPicture)
		delete m_pPicture;
	m_pPicture = nullptr;

	if (m_pCancel)
		delete m_pCancel;
	m_pCancel = nullptr;

	if (m_pMainFrame)
		delete m_pMainFrame;
	m_pMainFrame = nullptr;
}

/***************************************************
*登录确认等待时间
****************************************************
*/
bool LoginMessageBox::waitForConfirm(int msec)
{
	LoginMessageBox loginMessageBox;
	loginMessageBox.show();
	loginMessageBox.startTimer(msec);
	loginMessageBox.exec();

	return loginMessageBox.isLogin();
}

/***************************************************
*返回结果
****************************************************
*/
bool LoginMessageBox::isLogin()
{
	return m_bRet;
}

void LoginMessageBox::mouseMoveEvent(QMouseEvent * e)
{
	QWidget::mouseMoveEvent(e);
}

void LoginMessageBox::mousePressEvent(QMouseEvent * e)
{
	QWidget::mouseMoveEvent(e);
}

void LoginMessageBox::mouseReleaseEvent(QMouseEvent * e)
{
	QWidget::mouseMoveEvent(e);
}

void LoginMessageBox::initWidget()
{
	m_pMainFrame = new QFrame(this);
	m_pMainFrame->setObjectName("login_messagebox_frame");
	m_pMainFrame->resize(size());
	m_pMainFrame->move(0, 0);

	m_pPicture = new QLabel(m_pMainFrame);
	m_pPicture->setObjectName("login_messagebox_picture");
	m_pPicture->resize(100, 100);
	m_pPicture->move(70, 10);
	QMovie *movie = new QMovie(":/resource/messagebox/loading.gif");
	m_pPicture->setMovie(movie);
	m_pPicture->setScaledContents(true);
	movie->start();

	m_pCancel = new QPushButton("取消登录", m_pMainFrame);
	m_pCancel->setObjectName("login_messagebox_button");
	m_pCancel->resize(140, 30);
	m_pCancel->move(50, 120);

}

void LoginMessageBox::conn()
{
	//按钮事件
	connect(m_pCancel, &QPushButton::clicked, this, [this]() {
		m_bRet = false;
		stopTimer();
		close();
	});
}

void LoginMessageBox::startTimer(int msec)
{
	m_iTimerID = BasicMessageBox::startTimer(msec);
}

void LoginMessageBox::stopTimer()
{
	if (m_iTimerID)
		killTimer(m_iTimerID);

	m_iTimerID = 0;
}

void LoginMessageBox::timerEvent(QTimerEvent * e)
{
	close();
}
