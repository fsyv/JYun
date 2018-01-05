#include "stdafx.h"
#include "JYunBackup.h"

#include "backup/BackupLeftWidget.h"
#include "backup/BackupFileListWidget.h"

JYunBackup::JYunBackup()
{
	resize(800, 600);

	initWidget();
}


JYunBackup::~JYunBackup()
{
}

void JYunBackup::initWidget()
{
	m_pTitle = new QLabel("欢迎使用JYun", this);
	m_pTitle->resize(768, 60);
	m_pTitle->move(0, 0);
	m_pTitle->setAlignment(Qt::AlignCenter);
	m_pTitle->setFont(QFont("方正舒体", 25));


	m_pLeftWidget = new BackupLeftWidget(this);
	m_pLeftWidget->move(0, 60);


	m_pFileListWidget = new BackupFileListWidget(this);
	m_pFileListWidget->move(100, 60);
}
