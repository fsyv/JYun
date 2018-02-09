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
* @brief : �����ļ���
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/22
**/

#include "File.h"

class MusicFile : public File
{
public:
	MusicFile(QListWidgetItem *item = nullptr);
	~MusicFile();

	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();

	static bool isMusicFile(const QString &fileSuffix);

protected:
	void mouseDoubleClicked() override;
};

