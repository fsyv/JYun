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

#include "File.h"

class ImageFile : public File
{
	Q_OBJECT
public:
	ImageFile(QListWidgetItem *item = nullptr);
	~ImageFile();

	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();

	static bool isImageFile(const QString &fileSuffix);

protected:
	void mouseDoubleClicked() override;

private:

};

