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
* @brief : 视频文件类
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/22
**/

#include "File.h"

class VideoFile : public File
{
public:
	VideoFile(QListWidgetItem *item = nullptr);
	~VideoFile();

	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();
	
	static bool isVideoFile(const QString &fileSuffix);

protected:
	void mouseDoubleClicked() override;
};

