#include "stdafx.h"
#include "CloudDiskLeftWidget.h"

#include "logic\file\FileObject.h"

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

	init();
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
	m_pRootDirectory = new QPushButton("首页", this);
	m_pRootDirectory->setObjectName("clouddisk_left_button");
	m_pRootDirectory->resize(100, 35);
	m_pRootDirectory->move(0, 0);

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

void CloudDiskLeftWidget::conn()
{
	connect(m_pRootDirectory, &QPushButton::clicked, this, [this]() {
		emit rootClicked();
	});

	connect(m_pRecently, &QPushButton::clicked, this, [this](bool flag) {
		emit recentlyClicked(flag);
	});

	connect(m_pDocument, &QPushButton::clicked, this, &CloudDiskLeftWidget::documentButtonClick);
	connect(m_pPicture, &QPushButton::clicked, this, &CloudDiskLeftWidget::pictureButtonClick);
	connect(m_pVideo, &QPushButton::clicked, this, &CloudDiskLeftWidget::videoButtonClick);
	connect(m_pMusic, &QPushButton::clicked, this, &CloudDiskLeftWidget::musicButtonClick);

	connect(m_pSetup, &QPushButton::clicked, this, [this](bool flag) {
		emit setupClicked(flag);
	});
}

void CloudDiskLeftWidget::initData()
{
	m_iCurrentFileStyle = 0x00;
}

void CloudDiskLeftWidget::init()
{
	initWidget();

	conn();

	initData();
}

void CloudDiskLeftWidget::documentButtonClick(bool flag)
{
	if (flag)
		m_iCurrentFileStyle |= (int)FileObject::FileType::Document;
	else
		m_iCurrentFileStyle ^= (int)FileObject::FileType::Document;

	emit fileEchoChange(m_iCurrentFileStyle);
}

void CloudDiskLeftWidget::pictureButtonClick(bool flag)
{
	if (flag)
		m_iCurrentFileStyle |= (int)FileObject::FileType::Image;
	else
		m_iCurrentFileStyle ^= (int)FileObject::FileType::Image;

	emit fileEchoChange(m_iCurrentFileStyle);
}

void CloudDiskLeftWidget::videoButtonClick(bool flag)
{
	if (flag)
		m_iCurrentFileStyle |= (int)FileObject::FileType::Video;
	else
		m_iCurrentFileStyle ^= (int)FileObject::FileType::Video;

	emit fileEchoChange(m_iCurrentFileStyle);
}

void CloudDiskLeftWidget::musicButtonClick(bool flag)
{
	if (flag)
		m_iCurrentFileStyle |= (int)FileObject::FileType::Music;
	else
		m_iCurrentFileStyle ^= (int)FileObject::FileType::Music;

	emit fileEchoChange(m_iCurrentFileStyle);
}
