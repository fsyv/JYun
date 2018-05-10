#include "stdafx.h"
#include "JYunBackup.h"

#include "backup/BackupLeftWidget.h"
#include "backup/BackupFileListWidget.h"

JYunBackup::JYunBackup() :
	m_pListWidget(nullptr),
	m_pSetup(nullptr)
{
	changeWidgetSize(QSize(300, 400));

	init();
}


JYunBackup::~JYunBackup()
{
	if (m_pListWidget)
		delete m_pListWidget;
	m_pListWidget = nullptr;

	if (m_pSetup)
		delete m_pSetup;
	m_pSetup = nullptr;
}

void JYunBackup::initWidget()
{
	m_pListWidget = new QListWidget(this);
	m_pListWidget->setObjectName("backup_listwidget");
	m_pListWidget->resize(260, 300);
	m_pListWidget->move(20, 40);

	m_pSetup = new QPushButton("设  置", this);
	m_pSetup->setObjectName("backup_setup");
	m_pSetup->resize(260, 40);
	m_pSetup->move(20, 350);
	m_pSetup->setCheckable(true);

	m_pWidget = new QWidget(this);
	m_pWidget->resize(260, 300);
	m_pWidget->move(20, 40);
	m_pWidget->hide();

	m_label_date = new QLineEdit("备份时间: ", m_pWidget);
	m_label_date->setReadOnly(true);
	m_label_date->move(0, 80);
	m_label_date->resize(100, 40);
	m_label_date->setObjectName("disk_setup_label");
	m_label_date->setAlignment(Qt::AlignCenter);

	m_line_date = new QLineEdit(m_pWidget);
	m_line_date->move(100, 80);
	m_line_date->resize(160, 40);
	m_line_date->setObjectName("disk_setup_line");
	m_line_date->setText("30");

	m_label_dir = new QLineEdit("备份目录: ", m_pWidget);
	m_label_dir->setReadOnly(true);
	m_label_dir->move(0, 140);
	m_label_dir->resize(100, 40);
	m_label_dir->setObjectName("disk_setup_label");
	m_label_dir->setAlignment(Qt::AlignCenter);

	m_line_dir = new QLineEdit(m_pWidget);
	m_line_dir->setReadOnly(true);
	m_line_dir->move(100, 140);
	m_line_dir->resize(100, 40);
	m_line_dir->setObjectName("disk_setup_line");
	m_line_dir->setText("E:/backup");

	m_button_dir = new QPushButton("选择目录", m_pWidget);
	m_button_dir->move(200, 140);
	m_button_dir->resize(60, 40);
	m_button_dir->setObjectName("disk_setup_button");
}

void JYunBackup::conn()
{
	connect(m_pSetup, &QPushButton::clicked, this, [this](bool b) {
		m_pListWidget->setVisible(!b);
		m_pWidget->setVisible(b);
	});
}

void JYunBackup::initData()
{
	for (int i = 0; i < 5; ++i)
	{
		m_pListWidget->addItem(QString("2018年%1月1日备份了一次").arg(i + 1));
	}
}

void JYunBackup::init()
{
	initWidget();

	conn();

	initData();
}

void JYunBackup::resizeEvent(QResizeEvent * e)
{
	paintRoundRect();

	BasicWidget::resizeEvent(e);
}
