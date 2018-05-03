#include "stdafx.h"
#include "JYunSetup.h"

#include "messagebox\JYunMessageBox.h"
#include "logic/JYunTools.h"

#include "logic\file\ImageFile.h"
#include "logic\network\JYunTcp.h"
#include "logic\User.h"

JYunSetup::JYunSetup() :
	m_pChangeAvatarButton(nullptr),
	m_pUsernameLabel(nullptr),
	m_pUsernameLineEdit(nullptr),
	m_pUserpassLabel(nullptr),
	m_pUserpassLineEdit(nullptr),
	m_pCommitButton(nullptr),
	m_pHeadImage(nullptr)
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

	if (m_pHeadImage)
		delete m_pHeadImage;
	m_pHeadImage = nullptr;
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
	{
		//����������ʾͷ��
		m_pHeadImage->clear();
		m_pHeadImage->setLocalUrl(file.filePath());
		setAvatar(QPixmap(m_pHeadImage->localUrl().path()));
	}
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

void JYunSetup::updateHead(GetUserHead * gmsg)
{
	if (!gmsg)
		return;

	m_pHeadImage->setRemoteUrl(gmsg->m_aHeadUrl);

	m_pHeadImage->download();
}

void JYunSetup::headMd5(GetUserHeadMd5 * gmsg)
{
	if (!gmsg)
		return;

	if (m_pHeadImage->md5() != QString(gmsg->m_aMd5))
	{
		m_pHeadImage->remove();

		JYunTcp *network = GlobalParameter::getInstance()->getTcpNetwork();
		User *user = GlobalParameter::getInstance()->getUser();

		network->sendGetUserHead(user->getUsername());
	}
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

	//ע�������¼���
	JYunTcp *network = GlobalParameter::getInstance()->getTcpNetwork();
	connect(network, &JYunTcp::getUserHeadMsg, this, &JYunSetup::updateHead);
	connect(network, &JYunTcp::getUserHeadMd5Msg, this, &JYunSetup::headMd5);
}

void JYunSetup::initData()
{
	m_stFakePass = QString("��Ҫ͵������Ŷ!");

	User *user = GlobalParameter::getInstance()->getUser();

	//�����û����ͼ�����
	m_pUsernameLineEdit->setText(user->getUsername());
	m_pUserpassLineEdit->setText(m_stFakePass);

	updateAvatar();
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

	User *user = GlobalParameter::getInstance()->getUser();

	//����ͷ�����
	m_pHeadImage = new ImageFile;
	QString headPath = QDir::currentPath() + QString("/head/") + user->getUsername();
	m_pHeadImage->setLocalUrl(headPath);

	setAvatar(QPixmap(headPath));
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
