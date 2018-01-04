#include "stdafx.h"
#include "CloudDiskTopWidget.h"

CloudDiskTopWidget::CloudDiskTopWidget(QWidget *parent)
	: QFrame(parent),
	m_pUpload(nullptr),
	m_pBackward(nullptr),
	m_pForward(nullptr),
	m_pRefresh(nullptr),
	m_pDownload(nullptr),
	m_pShare(nullptr),
	m_pTaskList(nullptr)
{
	resize(800, 50);

	initWidget();
}

CloudDiskTopWidget::~CloudDiskTopWidget()
{
	if (m_pUpload)
		delete m_pUpload;
	m_pUpload = nullptr;

	if (m_pBackward)
		delete m_pBackward;
	m_pBackward = nullptr;

	if (m_pForward)
		delete m_pForward;
	m_pForward = nullptr;

	if (m_pRefresh)
		delete m_pRefresh;
	m_pRefresh = nullptr;

	if (m_pDownload)
		delete m_pDownload;
	m_pDownload = nullptr;

	if (m_pShare)
		delete m_pShare;
	m_pShare = nullptr;

	if (m_pTaskList)
		delete m_pTaskList;
	m_pTaskList = nullptr;
}

void CloudDiskTopWidget::setStyleSheetFromFile(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
		setStyleSheet(file.readAll());
}

void CloudDiskTopWidget::initWidget()
{
	m_pUpload = new QPushButton("上传", this);
	m_pUpload->setObjectName("clouddisk_top_upload");
	m_pUpload->resize(80, 35);
	m_pUpload->move(10, 8);

	m_pBackward = new QPushButton(this);
	m_pBackward->setObjectName("clouddisk_top_image");
	m_pBackward->resize(32, 32);
	m_pBackward->move(100, 8);
	m_pBackward->setIcon(QIcon(":/resource/clouddisk/button/backward.png"));
	m_pBackward->setIconSize(m_pBackward->size());
	m_pBackward->setToolTip("向后");

	m_pForward = new QPushButton(this);
	m_pForward->setObjectName("clouddisk_top_image");
	m_pForward->resize(32, 32);
	m_pForward->move(142, 8);
	m_pForward->setIcon(QIcon(":/resource/clouddisk/button/forward.png"));
	m_pForward->setIconSize(m_pForward->size());
	m_pForward->setToolTip("向前");

	m_pRefresh = new QPushButton(this);
	m_pRefresh->setObjectName("clouddisk_top_image");
	m_pRefresh->resize(32, 32);
	m_pRefresh->move(184, 8);
	m_pRefresh->setIcon(QIcon(":/resource/clouddisk/button/refresh.png"));
	m_pRefresh->setIconSize(m_pRefresh->size());
	m_pRefresh->setToolTip("刷新");

	m_pDownload = new QPushButton("下载", this);
	m_pDownload->setObjectName("clouddisk_top_download");
	m_pDownload->resize(120, 35);
	m_pDownload->move(400, 8);

	m_pShare = new QPushButton("分享", this);
	m_pShare->setObjectName("clouddisk_top_share");
	m_pShare->resize(120, 35);
	m_pShare->move(525, 8);

	m_pTaskList = new QPushButton("任务列表", this);
	m_pTaskList->setObjectName("clouddisk_top_task");
	m_pTaskList->resize(150, 50);
	m_pTaskList->move(650, 0);
}
