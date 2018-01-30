#include "stdafx.h"
#include "JYunRegister.h"

#include "logic/network/JYunHttp.h"
#include "logic/JYunTools.h"
#include "messagebox/JYunMessageBox.h"

JYunRegister::JYunRegister():
	m_pUsernameLabel(nullptr),
	m_pUsernameLineEdit(nullptr),
	m_pUserpassLabel(nullptr),
	m_pUserpassLineEdit(nullptr),
	m_pRegisterButton(nullptr)
{
	changeWidgetSize(QSize(300, 200));

	init();
}


JYunRegister::~JYunRegister()
{
	if (m_pUsernameLabel)
		delete m_pUsernameLabel;
	m_pUsernameLabel = nullptr;

	if (m_pUsernameLineEdit)
		delete m_pUsernameLineEdit;
	m_pUsernameLineEdit = nullptr;

	if (m_pUserpassLabel)
		delete m_pUserpassLabel;
	m_pUserpassLabel = nullptr;

	if (m_pUserpassLineEdit)
		delete m_pUserpassLineEdit;
	m_pUserpassLineEdit = nullptr;

	if (m_pRegisterButton)
		delete m_pRegisterButton;
	m_pRegisterButton = nullptr;
}

void JYunRegister::initWidget()
{
	m_pUsernameLabel = new QLineEdit(" �ʺ�:", this);
	m_pUsernameLabel->setObjectName("register_label");
	m_pUsernameLabel->resize(50, 30);
	m_pUsernameLabel->move(20, 55);
	m_pUsernameLabel->setDisabled(true);

	m_pUsernameLineEdit = new QLineEdit(this);
	m_pUsernameLineEdit->setObjectName("register_input");
	m_pUsernameLineEdit->resize(210, 30);
	m_pUsernameLineEdit->move(70, 55);
	m_pUsernameLineEdit->setPlaceholderText("�������û���!");
	m_pUsernameLineEdit->installEventFilter(this);

	m_pUserpassLabel = new QLineEdit(" ����:", this);
	m_pUserpassLabel->setObjectName("register_label");
	m_pUserpassLabel->resize(50, 30);
	m_pUserpassLabel->move(20, 95);
	m_pUserpassLabel->setDisabled(true);

	m_pUserpassLineEdit = new QLineEdit(this);
	m_pUserpassLineEdit->setObjectName("register_input");
	m_pUserpassLineEdit->resize(210, 30);
	m_pUserpassLineEdit->move(70, 95);
	m_pUserpassLineEdit->setEchoMode(QLineEdit::Password);
	m_pUserpassLineEdit->setPlaceholderText("����������!");

	m_pRegisterButton = new QPushButton("ע    ��", this);
	m_pRegisterButton->setObjectName("register_button");
	m_pRegisterButton->resize(180, 30);
	m_pRegisterButton->move(60, 145);
	m_pRegisterButton->setToolTip("�ύ");
}

void JYunRegister::conn()
{
	//ע�ᰴť�źŲ۰�
	connect(m_pRegisterButton, &QPushButton::clicked, this, &JYunRegister::registered);
}

void JYunRegister::initData()
{
}

void JYunRegister::init()
{
	initWidget();

	conn();

	initData();
}

void JYunRegister::usernameInputFocusOut()
{
	QString username = m_pUsernameLineEdit->text();
	JYunHttp http;
	if (http.checkUsername(username))
	{
		//�û����Ѿ�����
		JYunMessageBox::prompt("�û����Ѿ�����");
		m_pUsernameLineEdit->setFocus();
	}
}

void JYunRegister::resizeEvent(QResizeEvent * e)
{
	paintRoundRect();

	BasicWidget::resizeEvent(e);
}

bool JYunRegister::eventFilter(QObject * object, QEvent * e)
{
	if (object == m_pUsernameLineEdit)
	{
		if (e->type() == QEvent::FocusOut)
			usernameInputFocusOut();
	}

	return BasicWidget::eventFilter(object, e);
}

void JYunRegister::registered()
{
	if (m_pUsernameLineEdit->text().isEmpty())
	{
		//�û���Ϊ��
		JYunMessageBox::prompt("�û�������Ϊ��");
		m_pUsernameLineEdit->setFocus();
		return;
	}

	if (m_pUserpassLineEdit->text().isEmpty())
	{
		//����Ϊ��
		JYunMessageBox::prompt("���������룡");
		m_pUserpassLineEdit->setFocus();
		return;
	}

	QString username = m_pUsernameLineEdit->text();
	QString userpass = JYunTools::stringMD5(m_pUserpassLineEdit->text());

	JYunHttp http;
	QMap<QString, QString> result = http.registered(username, userpass);

	if (result.value("register_result") == QString("True"))
	{
		//ע��ɹ�
		JYunMessageBox::prompt("ע��ɹ���");
	}
	else
	{
		//ע��ʧ��
		JYunMessageBox::prompt(result.value("register_error"));
	}
}