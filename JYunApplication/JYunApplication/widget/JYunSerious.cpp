#include "stdafx.h"
#include "JYunSerious.h"

JYunSerious::JYunSerious():
	m_pPicture(nullptr),
	m_pText(nullptr),
	m_pContactLabel(nullptr),
	m_pContactInput(nullptr),
	m_pPlainTextEdit(nullptr),
	m_pCommit(nullptr),
	m_pCancel(nullptr)
{
	changeWidgetSize(QSize(300, 400));

	initWidget();
}


JYunSerious::~JYunSerious()
{
}

void JYunSerious::initWidget()
{
	m_pPicture = new QLabel(this);
	m_pPicture->setObjectName("serious_picture");
	m_pPicture->resize(48, 48);
	m_pPicture->move(35, 50);
	m_pPicture->setPixmap(QPixmap(":/resource/messagebox/sigh.png"));

	m_pText = new QLabel("发生了不可挽回的错误!", this);
	m_pText->setObjectName("serious_tip");
	m_pText->resize(215, 48);
	m_pText->move(85, 50);
	m_pText->setAlignment(Qt::AlignCenter);
	m_pText->setFont(QFont("方正舒体", 10));

	m_pContactLabel = new QLineEdit(" 联系方式:", this);
	m_pContactLabel->setObjectName("serious_input_left");
	m_pContactLabel->resize(90, 35);
	m_pContactLabel->move(30, 110);
	m_pContactLabel->setEnabled(false);

	m_pContactInput = new QLineEdit(this);
	m_pContactInput->setObjectName("serious_input_right");
	m_pContactInput->resize(150, 35);
	m_pContactInput->move(120, 110);
	m_pContactInput->setPlaceholderText("QQ/手机/邮箱");

	m_pPlainTextEdit = new QPlainTextEdit(this);
	m_pPlainTextEdit->setObjectName("serious_plaintextedit");
	m_pPlainTextEdit->resize(240, 180);
	m_pPlainTextEdit->move(30, 155);
	m_pPlainTextEdit->setPlaceholderText("请留下您相对我们说的话……");

	m_pCommit = new QPushButton("提交", this);
	m_pCommit->setObjectName("serious_commit");
	m_pCommit->resize(105, 30);
	m_pCommit->move(30, 345);

	m_pCancel = new QPushButton("取消", this);
	m_pCancel->setObjectName("serious_cancel");
	m_pCancel->resize(105, 30);
	m_pCancel->move(165, 345);
}

void JYunSerious::resizeEvent(QResizeEvent * e)
{
	paintRoundRect();

	BasicWidget::resizeEvent(e);
}
