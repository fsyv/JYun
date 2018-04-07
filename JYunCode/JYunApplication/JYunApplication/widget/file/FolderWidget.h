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
* @brief : ÎÄ¼þ¼ÐÀà
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/21
**/

#include "FileObjectWidget.h"

class Folder;

class FolderWidget : public FileObjectWidget
{
	Q_OBJECT
public:
	explicit FolderWidget(Folder *file, QWidget *parent = nullptr);
	~FolderWidget();

protected:
	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();

	void mouseDoubleClicked() override;

protected slots:
	void openFolder(Folder *folder);

signals:
	void open(Folder *);
};