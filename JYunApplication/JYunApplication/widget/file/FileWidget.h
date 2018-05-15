#pragma once
#pragma execution_character_set("utf-8")

/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 所有文件的公共类，文件总共分为：1.文档；2.图片；3.视频；4音乐；5.其它
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/21
**/

#include "FileObjectWidget.h"

class File;

class FileWidget : public FileObjectWidget
{
	Q_OBJECT
public:
	explicit FileWidget(File *file, QWidget *parent = nullptr);
	~FileWidget();

	void mouseDoubleClicked() override;
};