#include "stdafx.h"
#include "JYunSetup.h"

#include "messagebox\JYunMessageBox.h"

JYunSetup::JYunSetup(QString username) :
	m_pChangeAvatarButton(nullptr),
	m_pUsernameLabel(nullptr),
	m_pUsernameLineEdit(nullptr),
	m_pUserpassLabel(nullptr),
	m_pUserpassLineEdit(nullptr),
	m_pCommitButton(nullptr),
	m_stUsername(username)
{
	changeWidgetSize(QSize(300, 400));

	init();
}


JYunSetup::~JYunSetup()
{
	if (m_pChangeAvatarButton)
		delete m_pChangeAvatarButton;
	m_pChangeAvatarButton = nullptr;

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

	if (m_pCommitButton)
		delete m_pCommitButton;
	m_pCommitButton = nullptr;
}

void JYunSetup::setAvatar(const QPixmap & pixmap)
{
	QIcon icon(pixmap);

	m_pChangeAvatarButton->setIcon(icon);
	m_pChangeAvatarButton->setIconSize(m_pChangeAvatarButton->size());
}

/***************************************************
*����ͷ��ť��Ӧ����
****************************************************
*/
void JYunSetup::changeHead()
{
	QString filePath = QFileDialog::getOpenFileName(
		this,
		QString("ѡ��ͼ��"),
		QDir::homePath().append("/Desktop"),
		QString("Images (*.png *.jpg)")
	);

	if (filePath.isEmpty())
		return;

	QFileInfo file(filePath);

	if (file.exists())
		//����������ʾͷ��
		setAvatar(QPixmap(file.filePath()));
	else
		JYunMessageBox::prompt(QString("�ļ�������!"));
}

/***************************************************
*�ύ��ť��Ӧ����
****************************************************
*/
void JYunSetup::commit()
{
	//���ͷ���Ƿ�ı�
	//��������Ƿ�ı�

}

void JYunSetup::initWidget()
{
	m_pChangeAvatarButton = new QPushButton(this);
	m_pChangeAvatarButton->setObjectName("setup_change");
	m_pChangeAvatarButton->resize(100, 100);
	m_pChangeAvatarButton->move(100, 30);
	m_pChangeAvatarButton->setToolTip(QString("����ͷ��"));

	m_pUsernameLabel = new QLineEdit(" �ʺ�:", this);
	m_pUsernameLabel->setObjectName("setup_label");
	m_pUsernameLabel->resize(50, 30);
	m_pUsernameLabel->move(20, 200);
	m_pUsernameLabel->setDisabled(true);

	m_pUsernameLineEdit = new QLineEdit(this);
	m_pUsernameLineEdit->setObjectName("setup_input");
	m_pUsernameLineEdit->resize(210, 30);
	m_pUsernameLineEdit->move(70, 200);
	//�ʺ�����Ϊ���ɱ༭
	m_pUsernameLineEdit->setDisabled(true);

	m_pUserpassLabel = new QLineEdit(" ����:", this);
	m_pUserpassLabel->setObjectName("setup_label");
	m_pUserpassLabel->resize(50, 30);
	m_pUserpassLabel->move(20, 240);
	m_pUserpassLabel->setDisabled(true);

	m_pUserpassLineEdit = new QLineEdit(this);
	m_pUserpassLineEdit->setObjectName("setup_input");
	m_pUserpassLineEdit->resize(210, 30);
	m_pUserpassLineEdit->move(70, 240);
	m_pUserpassLineEdit->setEchoMode(QLineEdit::Password);
	m_pUserpassLineEdit->setPlaceholderText("�������µ�����!");
	m_pUserpassLineEdit->installEventFilter(this);

	m_pCommitButton = new QPushButton("��    ��", this);
	m_pCommitButton->setObjectName("setup_commit");
	m_pCommitButton->resize(180, 30);
	m_pCommitButton->move(60, 320);
	m_pCommitButton->setToolTip("�ύ�޸�");
}

void JYunSetup::conn()
{
	//����ͷ��ť�źŲ۰�
	connect(m_pChangeAvatarButton, &QPushButton::clicked, this, &JYunSetup::changeHead);

	//�ύͷ��ť�źŲ۰�
	connect(m_pCommitButton, &QPushButton::clicked, this, &JYunSetup::commit);
}

void JYunSetup::initData()
{
	m_stFakePass = QString("��Ҫ͵������Ŷ!");

	//�����û����ͼ�����
	m_pUsernameLineEdit->setText(m_stUsername);
	m_pUserpassLineEdit->setText(m_stFakePass);
}

void JYunSetup::init()
{
	initWidget();

	conn();

	initData();
}

/***************************************************
*�����������õ�����
****************************************************
*/
void JYunSetup::passInputFocusIn()
{
	m_pUserpassLineEdit->setText(m_stRealPass);
}

/***************************************************
*����������ʧȥ����
****************************************************
*/
void JYunSetup::passInputFocusOut()
{
	m_stRealPass = m_pUserpassLineEdit->text();
	m_pUserpassLineEdit->setText(m_stFakePass);
}

/***************************************************
*�ӷ�������ȡ���ݸ���ͷ��
****************************************************
*/
void JYunSetup::updateAvatar()
{
	//���㱾��ͷ���MD5ֵ
	//������������ͬ��ʹ�ñ��ػ���ͼƬ
	//��������������ͬ��ӷ���������ͼƬ
}

void JYunSetup::resizeEvent(QResizeEvent * e)
{
	paintRoundRect();

	BasicWidget::resizeEvent(e);
}

bool JYunSetup::eventFilter(QObject * object, QEvent * e)
{
	if (object == m_pUserpassLineEdit)
	{
		if (e->type() == QEvent::FocusIn)
			passInputFocusIn();
		else if (e->type() == QEvent::FocusOut)
			passInputFocusOut();
	}
	return BasicWidget::eventFilter(object, e);
}
