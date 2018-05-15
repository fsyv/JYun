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
	((File *)m_pFile)->preview();
}