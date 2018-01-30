#include "stdafx.h"
#include "FileObject.h"

FileObject::FileObject(QListWidget *parent):
	QFrame(),
	m_pConfirmCheckBox(nullptr),
	m_pPictureLabel(nullptr),
	m_pNameLabel(nullptr),
	m_pMenu(nullptr)
{
	setStyleSheetFromFile(":/resource/qss/file.qss");

	m_pListWidgetItem = new QListWidgetItem(parent);

	init();
}

FileObject::FileObject(QString name, FileType type, QListWidget * parent):
	FileObject(parent)
{
	m_stFileName = name;
	m_eFileType = type;

	setNameLabel(m_stFileName);
}

FileObject::~FileObject()
{
	destroyWidget();
	destroyItem();
}

void FileObject::setStyleSheetFromFile(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
		setStyleSheet(file.readAll());
	file.close();
}

/***************************************************
*����ͼƬ��ʾ����
****************************************************
*/
void FileObject::setPicture(const QString &resource)
{
	m_pPictureLabel->setPixmap(QPixmap(resource));
}

/***************************************************
*�����ļ�����ʾ
****************************************************
*/
void FileObject::setNameLabel(const QString &name)
{
	m_pNameLabel->setText(name);
}

void FileObject::setFileName(const QString & name)
{
	m_stFileName = name;
}

void FileObject::setFilePath(const QString & path)
{
	m_stFilePath = path;
}

void FileObject::setConfirmCheckBoxStatus(bool status)
{
	m_pConfirmCheckBox->setChecked(status);
	m_pConfirmCheckBox->setVisible(status);
}

FileObject::FileType FileObject::fileType() const
{
	return m_eFileType;
}

QListWidgetItem * FileObject::item() const
{
	return m_pListWidgetItem;
}

QString FileObject::fileName() const
{
	return m_stFileName;
}

QString FileObject::filePath() const
{
	return m_stFilePath;
}

QString FileObject::fileNamePath() const
{
	return filePath() + fileName();
}

void FileObject::initWidget()
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

	m_pNameLabel = new QLabel(this);
	m_pNameLabel->setObjectName("fileobject_namelabel");
	m_pNameLabel->resize(125, 51);
	m_pNameLabel->move(0, 74);
	m_pNameLabel->setAlignment(Qt::AlignCenter);

	//��ʼ���˵�
	m_pMenu = new QMenu(this);
}

void FileObject::conn()
{
}

void FileObject::initData()
{
	//����ÿ����Ԫ��Ĵ�С
	m_pListWidgetItem->setSizeHint(QSize(125, 125));
}

void FileObject::init()
{
	initWidget();

	conn();

	initData();
}

void FileObject::destroyWidget()
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

void FileObject::destroyItem()
{

}

void FileObject::enterEvent(QEvent * e)
{
	m_pConfirmCheckBox->show();
}

void FileObject::leaveEvent(QEvent * e)
{
	if (!m_pConfirmCheckBox->isChecked())
		m_pConfirmCheckBox->hide();
}

void FileObject::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
		mouseLeftClicked();
	else if (e->button() == Qt::RightButton)
		mouseRightClicked();
	else
		QFrame::mousePressEvent(e);
}

void FileObject::mouseDoubleClickEvent(QMouseEvent * e)
{
	if(e->button() == Qt::LeftButton)
		mouseDoubleClicked();
	else
	    QFrame::mouseDoubleClickEvent(e);
}

void FileObject::mouseLeftClicked()
{

}

void FileObject::mouseRightClicked()
{
	if (m_pMenu->isEmpty())
		return;

	m_pMenu->move(cursor().pos());
	m_pMenu->show();
}
