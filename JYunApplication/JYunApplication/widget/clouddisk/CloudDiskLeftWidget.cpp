#include "stdafx.h"
#include "CloudDiskLeftWidget.h"

CloudDiskLeftWidget::CloudDiskLeftWidget(QWidget *parent):
	QFrame(parent),
	m_pRootDirectory(nullptr),
	m_pRecently(nullptr),
	m_pSortFrame(nullptr),
	m_pDocument(nullptr),
	m_pPicture(nullptr),
	m_pVideo(nullptr),
	m_pMusic(nullptr),
	m_pSetup(nullptr)
{
	resize(100, 490);

	initWidget();
}


CloudDiskLeftWidget::~CloudDiskLeftWidget()
{
	if (m_pRootDirectory)
		delete m_pRootDirectory;
	m_pRootDirectory = nullptr;

	if (m_pRecently)
		delete m_pRecently;
	m_pRecently = nullptr;

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

void CloudDiskLeftWidget::initWidget()
{
	m_pRootDirectory = new QPushButton("根目录", this);
	m_pRootDirectory->setObjectName("clouddisk_left_button");
	m_pRootDirectory->resize(100, 35);
	m_pRootDirectory->move(0, 0);
	m_pRootDirectory->setCheckable(true);

	m_pRecently = new QPushButton("时间线", this);
	m_pRecently->setObjectName("clouddisk_left_button");
	m_pRecently->resize(100, 35);
	m_pRecently->move(0, 35);
	m_pRecently->setCheckable(true);

	m_pSortFrame = new QFrame(this);
	m_pSortFrame->setObjectName("clouddisk_left_sort");
	m_pSortFrame->resize(100, 170);
	m_pSortFrame->move(0, 90);

	m_pDocument = new QPushButton("文档", m_pSortFrame);
	m_pDocument->setObjectName("clouddisk_left_button");
	m_pDocument->resize(100, 35);
	m_pDocument->move(0, 10);
	m_pDocument->setCheckable(true);

	m_pPicture = new QPushButton("图片", m_pSortFrame);
	m_pPicture->setObjectName("clouddisk_left_button");
	m_pPicture->resize(100, 35);
	m_pPicture->move(0, 45);
	m_pPicture->setCheckable(true);

	m_pVideo = new QPushButton("视频", m_pSortFrame);
	m_pVideo->setObjectName("clouddisk_left_button");
	m_pVideo->resize(100, 35);
	m_pVideo->move(0, 80);
	m_pVideo->setCheckable(true);

	m_pMusic = new QPushButton("音乐", m_pSortFrame);
	m_pMusic->setObjectName("clouddisk_left_button");
	m_pMusic->resize(100, 35);
	m_pMusic->move(0, 115);
	m_pMusic->setCheckable(true);

	m_pSetup = new QPushButton("设置", this);
	m_pSetup->setObjectName("clouddisk_left_button");
	m_pSetup->resize(100, 35);
	m_pSetup->move(0, 270);
	m_pSetup->setCheckable(true);
}
