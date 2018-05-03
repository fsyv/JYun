#include "stdafx.h"
#include "FileWidget.h"

#include "logic\file\File.h"

FileWidget::FileWidget(File *file, QWidget *parent):
	FileObjectWidget(file, parent)
{

}

FileWidget::~FileWidget()
{
}

void FileWidget::mouseDoubleClicked()
{
}

void FileWidget::upload()
{

}

void FileWidget::download()
{
	m_pFile->download();
}

void FileWidget::clear()
{
	m_pFile->upload();
}
