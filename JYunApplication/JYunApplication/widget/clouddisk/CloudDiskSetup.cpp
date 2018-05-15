#include "stdafx.h"
#include "CloudDiskSetup.h"

#include "logic/User.h"
#include "database/Database.h"

CloudDiskSetup::CloudDiskSetup(QWidget *parent) :
	QFrame(parent)
{
	resize(700, 490);
	init();
}


CloudDiskSetup::~CloudDiskSetup()
{
}

void CloudDiskSetup::initWidget()
{
	m_label = new QLineEdit("保存路径: ", this);
	m_label->setReadOnly(true);
	m_label->move(60, 60);
	m_label->resize(140, 40);
	m_label->setObjectName("disk_setup_label");
	m_label->setAlignment(Qt::AlignCenter);

	m_line = new QLineEdit(this);
	m_line->setReadOnly(true);
	m_line->move(200, 60);
	m_line->resize(300, 40);
	m_line->setObjectName("disk_setup_line");

	m_button = new QPushButton("选择目录", this);
	m_button->move(540, 65);
	m_button->resize(120, 30);
	m_button->setObjectName("disk_setup_button");
}

void CloudDiskSetup::conn()
{
	connect(m_button, &QPushButton::clicked, this, &CloudDiskSetup::clicked);
}

void CloudDiskSetup::initData()
{
	Database db;

	QString path = db.getDownloadPath();
	m_line->setText(path);
	User *user = GlobalParameter::getInstance()->getUser();
	user->setDownloadPath(path);
}

void CloudDiskSetup::init()
{
	initWidget();

	conn();

	initData();
}

void CloudDiskSetup::clicked()
{
	QString path = QFileDialog::getExistingDirectory(
		this,
		QString("选择文件夹"),
		QDir::homePath().append("/Desktop")
	);

	if (path.isEmpty())
		return;

	m_line->setText(path);

	User *user = GlobalParameter::getInstance()->getUser();
	user->setDownloadPath(path);

	Database db;
	db.setDownloadPath(path);
}
