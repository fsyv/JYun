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
* @brief : 文件夹类
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
	
	//文件列表信号槽绑定
	void connFiles(QList<FileObject *> &files);

	void mouseDoubleClicked() override;

protected slots:
	void openFolder(Folder *folder);

signals:
	void open(Folder *);
};