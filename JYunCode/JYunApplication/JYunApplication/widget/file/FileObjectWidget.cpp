#include "stdafx.h"
#include "FileObjectWidget.h"

#include "logic\file\FileObject.h"

#include "FolderWidget.h"
#include "DocumentFileWidget.h"
#include "ImageFileWidget.h"
#include "MusicFileWidget.h"
#include "VideoFileWidget.h"
#include "OtherFileWidget.h"

FileObjectWidget::FileObjectWidget(FileObject *file, QWidget *parent):
	QFrame(parent),
	m_pConfirmCheckBox(nullptr),
	m_pPictureLabel(nullptr),
	m_pNameLabel(nullptr),
	m_pMenu(nullptr),
	m_pFile(file)
{
	setStyleSheetFromFile(":/resource/qss/file.qss");

	init();
}

FileObjectWidget::~FileObjectWidget()
{
	destroyWidget();
}

void FileObjectWidget::setStyleSheetFromFile(QString filename)
{
	QFile file(filename);

	if (file.open(QIODevice::ReadOnly))
		setStyleSheet(file.readAll());
	file.close();
}

/***************************************************
*设置图片显示类容
****************************************************
*/
void FileObjectWidget::setPicture(const QString &resource)
{
	m_pPictureLabel->setPixmap(QPixmap(resource));
}

/***************************************************
*设置文件名显示
****************************************************
*/
void FileObjectWidget::setNameLabel(const QString &name)
{
	m_pNameLabel->setText(name);
}

void FileObjectWidget::setConfirmCheckBoxStatus(bool status)
{
	m_pConfirmCheckBox->setChecked(status);
	m_pConfirmCheckBox->setVisible(status);
}

FileObject * FileObjectWidget::file() const
{
	return m_pFile;
}

void FileObjectWidget::copy()
{
}

void FileObjectWidget::move()
{
}

void FileObjectWidget::rename()
{
}

void FileObjectWidget::upload()
{
}

void FileObjectWidget::download()
{
}

void FileObjectWidget::clear()
{
}

FileObjectWidget * FileObjectWidget::createWidget(FileObject *file)
{
	FileObjectWidget *widget = nullptr;

	switch (file->fileType())
	{
	case FileType::Folder:
		widget = new FolderWidget((Folder *)file);
		break;
	case FileType::Document:
		widget = new DocumentFileWidget((DocumentFile *)file);
		break;
	case FileType::Image:
		widget = new ImageFileWidget((ImageFile *)file);
		break;
	case FileType::Music:
		widget = new MusicFileWidget((MusicFile *)file);
		break;
	case FileType::Video:
		widget = new VideoFileWidget((VideoFile *)file);
		break;
	default:
		widget = new OtherFileWidget((OtherFile *)file);
		break;
	}

	return widget;
}

void FileObjectWidget::initWidget()
{
	resize(QSize(125, 125));

	m_pConfirmCheckBox = new QCheckBox(this);
	m_pConfirmCheckBox->setObjectName("fileobject_checkbox");
	m_pConfirmCheckBox->resize(16, 16);
	m_pConfirmCheckBox->move(5, 5);
	m_pConfirmCheckBox->hide();

	m_pPictureLabel = new QLabel(this);
	m_pPictureLabel->setObjectName("fileobject_picturelabel");
	m_pPictureLabel->resize(64, 64);
	m_pPictureLabel->move(32, 10);

	m_pNameLabel = new QLabel(m_pFile->fileName(), this);
	m_pNameLabel->setObjectName("fileobject_namelabel");
	m_pNameLabel->resize(125, 51);
	m_pNameLabel->move(0, 74);
	m_pNameLabel->setAlignment(Qt::AlignCenter);

	//初始化菜单
	m_pMenu = new QMenu(this);
}

void FileObjectWidget::conn()
{
}

void FileObjectWidget::initData()
{

}

void FileObjectWidget::init()
{
	initWidget();

	conn();

	initData();
}

void FileObjectWidget::destroyWidget()
{
	if (m_pConfirmCheckBox)
		delete m_pConfirmCheckBox;
	m_pConfirmCheckBox = nullptr;

	if (m_pPictureLabel)
		delete m_pPictureLabel;
	m_pPictureLabel = nullptr;

	if (m_pNameLabel)
		delete m_pNameLabel;
	m_pNameLabel = nullptr;

	if (m_pMenu)
		delete m_pMenu;
	m_pMenu = nullptr;
}

void FileObjectWidget::enterEvent(QEvent * e)
{
	m_pConfirmCheckBox->show();
}

void FileObjectWidget::leaveEvent(QEvent * e)
{
	if (!m_pConfirmCheckBox->isChecked())
		m_pConfirmCheckBox->hide();
}

void FileObjectWidget::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
		mouseLeftClicked();
	else if (e->button() == Qt::RightButton)
		mouseRightClicked();
	else
		QFrame::mousePressEvent(e);
}

void FileObjectWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
	if(e->button() == Qt::LeftButton)
		mouseDoubleClicked();
	else
	    QFrame::mouseDoubleClickEvent(e);
}

void FileObjectWidget::mouseLeftClicked()
{
	m_pConfirmCheckBox->setChecked(!m_pConfirmCheckBox->isChecked());
}

void FileObjectWidget::mouseRightClicked()
{
	if (m_pMenu->isEmpty())
		return;

	m_pMenu->move(cursor().pos());
	m_pMenu->show();
}
