#include "stdafx.h"
#include "BackupLeftWidget.h"


BackupLeftWidget::BackupLeftWidget(QWidget *parent):
	QFrame(parent),
	m_pRootDirectory(nullptr),
	m_pDelete(nullptr),
	m_pShare(nullptr),
	m_pSortFrame(nullptr),
	m_pDocument(nullptr),
	m_pPicture(nullptr),
	m_pVideo(nullptr),
	m_pMusic(nullptr),
	m_pSetup(nullptr)
{
	resize(100, 540);

	initWidget();
}


BackupLeftWidget::~BackupLeftWidget()
{
	if (m_pRootDirectory)
		delete m_pRootDirectory;
	m_pRootDirectory = nullptr;

	if (m_pDelete)
		delete m_pDelete;
	m_pDelete = nullptr;

	if (m_pShare)
		delete m_pShare;
	m_pShare = nullptr;

	if (m_pDocument)
		delete m_pDocument;
	m_pDocument = nullptr;

	if (m_pPicture)
		delete m_pPicture;
	m_pPicture = nullptr;

	if (m_pVideo)
		delete m_pVideo;
	m_pVideo = nullptr;

	if (m_pMusic)
		delete m_pMusic;
	m_pMusic = nullptr;

	if (m_pSortFrame)
		delete m_pSortFrame;
	m_pSortFrame = nullptr;

	if (m_pSetup)
		delete m_pSetup;
	m_pSetup = nullptr;
}

void BackupLeftWidget::initWidget()
{
	m_pRootDirectory = new QPushButton("¸ùÄ¿Â¼", this);
	m_pRootDirectory->setObjectName("backup_left_button");
	m_pRootDirectory->resize(100, 35);
	m_pRootDirectory->move(0, 0);
	m_pRootDirectory->setCheckable(true);

	m_pDelete = new QPushButton("É¾³ý", this);
	m_pDelete->setObjectName("backup_left_button");
	m_pDelete->resize(100, 35);
	m_pDelete->move(0, 35);
	m_pDelete->setCheckable(true);

	m_pShare = new QPushButton("·ÖÏí", this);
	m_pShare->setObjectName("backup_left_button");
	m_pShare->resize(100, 35);
	m_pShare->move(0, 70);
	m_pShare->setCheckable(true);

	m_pSortFrame = new QFrame(this);
	m_pSortFrame->setObjectName("backup_left_sort");
	m_pSortFrame->resize(100, 170);
	m_pSortFrame->move(0, 125);

	m_pDocument = new QPushButton("ÎÄµµ", m_pSortFrame);
	m_pDocument->setObjectName("backup_left_button");
	m_pDocument->resize(100, 35);
	m_pDocument->move(0, 10);
	m_pDocument->setCheckable(true);

	m_pPicture = new QPushButton("Í¼Æ¬", m_pSortFrame);
	m_pPicture->setObjectName("backup_left_button");
	m_pPicture->resize(100, 35);
	m_pPicture->move(0, 45);
	m_pPicture->setCheckable(true);

	m_pVideo = new QPushButton("ÊÓÆµ", m_pSortFrame);
	m_pVideo->setObjectName("backup_left_button");
	m_pVideo->resize(100, 35);
	m_pVideo->move(0, 80);
	m_pVideo->setCheckable(true);

	m_pMusic = new QPushButton("ÒôÀÖ", m_pSortFrame);
	m_pMusic->setObjectName("backup_left_button");
	m_pMusic->resize(100, 35);
	m_pMusic->move(0, 115);
	m_pMusic->setCheckable(true);

	m_pSetup = new QPushButton("ÉèÖÃ", this);
	m_pSetup->setObjectName("backup_left_button");
	m_pSetup->resize(100, 35);
	m_pSetup->move(0, 305);
	m_pSetup->setCheckable(true);
}
