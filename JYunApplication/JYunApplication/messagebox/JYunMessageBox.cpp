#include "stdafx.h"
#include "JYunMessageBox.h"


JYunMessageBox::JYunMessageBox(const QString &string, const Type &type):
	m_pPicture(nullptr),
	m_pText(nullptr),
	m_pPushButton(nullptr)
{
	m_stInfo = string;
	m_eType = type;
	changeWidgetSize(QSize(300, 180));

	initWidget();

	setWindowModality(Qt::ApplicationModal);
}


JYunMessageBox::~JYunMessageBox()
{
	if (m_pPicture)
		delete m_pPicture;
	m_pPicture = nullptr;

	if (m_pText)
		delete m_pText;
	m_pText = nullptr;

	if (m_pPushButton)
		delete m_pPushButton;
	m_pPushButton = nullptr;
}

void JYunMessageBox::prompt(const QString & string)
{
	JYunMessageBox w(string, Type::Prompt);
	w.show();
	w.exec();
}

void JYunMessageBox::success()
{
	JYunMessageBox w("操作成功", Type::Success);
	w.show();
	w.exec();
}

void JYunMessageBox::failed()
{
	JYunMessageBox w("操作失败", Type::Failed);
	w.show();
	w.exec();
}

void JYunMessageBox::initWidget()
{
	m_pPicture = new QLabel(this);
	m_pPicture->setObjectName("messagebox_picture");
	m_pPicture->move(52, 52);
	m_pPicture->resize(48, 48);
	setPicture();

	m_pText = new QLabel(m_stInfo, this);
	m_pText->setObjectName("messagebox_text");
	m_pText->move(110, 52);
	m_pText->resize(190, 48);
	m_pText->setAlignment(Qt::AlignCenter);
	m_pText->setFont(QFont("方正舒体", 10));

	m_pPushButton = new QPushButton("确  定", this);
	m_pPushButton->setObjectName("messagebox_button");
	m_pPushButton->move(90, 130);
	m_pPushButton->resize(120, 30);
	connect(m_pPushButton, &QPushButton::clicked, this, &JYunMessageBox::close);
}

void JYunMessageBox::setPicture()
{
	switch (m_eType) {
	case Type::Prompt :
		m_pPicture->setPixmap(QPixmap(":/resource/messagebox/prompt.png"));
		break;
	case Type::Success:
		m_pPicture->setPixmap(QPixmap(":/resource/messagebox/success.png"));
		break;
	case Type::Failed:
		m_pPicture->setPixmap(QPixmap(":/resource/messagebox/failed.png"));
		break;
	}
}

//void JYunMessageBox::resizeEvent(QResizeEvent * e)
//{
//	paintRoundRect();
//
//	BasicWidget::resizeEvent(e);
//}
