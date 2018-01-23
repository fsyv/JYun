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

#include "FileObject.h"

class Folder : public FileObject
{
	Q_OBJECT
public:
	explicit Folder(QString name, QListWidget *parent = nullptr);
	~Folder();

	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();

protected:
	void mouseDoubleClicked() override;

private:
	
};

