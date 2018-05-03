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
*更换头像按钮响应函数
****************************************************
*/
void JYunSetup::changeHead()
{
	QString filePath = QFileDialog::getOpenFileName(
		this,
		QString("选择图像"),
		QDir::homePath().append("/Desktop"),
		QString("Images (*.png *.jpg)")
	);

	if (filePath.isEmpty())
		return;

	QFileInfo file(filePath);

	if (file.exists())
	{
		//更换界面显示头像
		m_pHeadImage->clear();
		m_pHeadImage->setLocalUrl(file.filePath());
		setAvatar(QPixmap(m_pHeadImage->localUrl().path()));
	}
	else
		JYunMessageBox::prompt(QString("文件不存在!"));
}

/***************************************************
*提交按钮响应函数
****************************************************
*/
void JYunSetup::commit()
{
	//检测头像是否改变
	//检测密码是否改变

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
	m_pChangeAvatarButton->setToolTip(QString("更换头像"));

	m_pUsernameLabel = new QLineEdit(" 帐号:", this);
	m_pUsernameLabel->setObjectName("setup_label");
	m_pUsernameLabel->resize(50, 30);
	m_pUsernameLabel->move(20, 200);
	m_pUsernameLabel->setDisabled(true);

	m_pUsernameLineEdit = new QLineEdit(this);
	m_pUsernameLineEdit->setObjectName("setup_input");
	m_pUsernameLineEdit->resize(210, 30);
	m_pUsernameLineEdit->move(70, 200);
	//帐号设置为不可编辑
	m_pUsernameLineEdit->setDisabled(true);

	m_pUserpassLabel = new QLineEdit(" 密码:", this);
	m_pUserpassLabel->setObjectName("setup_label");
	m_pUserpassLabel->resize(50, 30);
	m_pUserpassLabel->move(20, 240);
	m_pUserpassLabel->setDisabled(true);

	m_pUserpassLineEdit = new QLineEdit(this);
	m_pUserpassLineEdit->setObjectName("setup_input");
	m_pUserpassLineEdit->resize(210, 30);
	m_pUserpassLineEdit->move(70, 240);
	m_pUserpassLineEdit->setEchoMode(QLineEdit::Password);
	m_pUserpassLineEdit->setPlaceholderText("请输入新的密码!");
	m_pUserpassLineEdit->installEventFilter(this);

	m_pCommitButton = new QPushButton("提    交", this);
	m_pCommitButton->setObjectName("setup_commit");
	m_pCommitButton->resize(180, 30);
	m_pCommitButton->move(60, 320);
	m_pCommitButton->setToolTip("提交修改");
}

void JYunSetup::conn()
{
	//更换头像按钮信号槽绑定
	connect(m_pChangeAvatarButton, &QPushButton::clicked, this, &JYunSetup::changeHead);

	//提交头像按钮信号槽绑定
	connect(m_pCommitButton, &QPushButton::clicked, this, &JYunSetup::commit);

	//注册网络事件绑定
	JYunTcp *network = GlobalParameter::getInstance()->getTcpNetwork();
	connect(network, &JYunTcp::getUserHeadMsg, this, &JYunSetup::updateHead);
	connect(network, &JYunTcp::getUserHeadMd5Msg, this, &JYunSetup::headMd5);
}

void JYunSetup::initData()
{
	m_stFakePass = QString("不要偷看密码哦!");

	User *user = GlobalParameter::getInstance()->getUser();

	//设置用户名和假密码
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
*密码输入栏得到焦点
****************************************************
*/
void JYunSetup::passInputFocusIn()
{
	m_pUserpassLineEdit->setText(m_stRealPass);
}

/***************************************************
*密码输入栏失去焦点
****************************************************
*/
void JYunSetup::passInputFocusOut()
{
	m_stRealPass = m_pUserpassLineEdit->text();
	m_pUserpassLineEdit->setText(m_stFakePass);
}

/***************************************************
*从服务器获取数据更新头像
****************************************************
*/
void JYunSetup::updateAvatar()
{
	//计算本地头像的MD5值
	//如果与服务器相同则使用本地缓存图片
	//如果与服务器不相同则从服务器下载图片

	User *user = GlobalParameter::getInstance()->getUser();

	//本地头像对象
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
