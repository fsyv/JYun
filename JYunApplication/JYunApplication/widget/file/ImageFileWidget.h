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
* @brief : Í¼Æ¬ÎÄ¼þÀà
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/22
**/

#include "FileWidget.h"

class ImageFile;

class ImageFileWidget : public FileWidget
{
	Q_OBJECT
public:
	ImageFileWidget(ImageFile *file, QWidget *parent = nullptr);
	~ImageFileWidget();

	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();

protected:
	void mouseDoubleClicked() override;
};

