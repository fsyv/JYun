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
* @brief : “Ù¿÷Œƒº˛¿‡
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/22
**/

#include "FileWidget.h"

class MusicFile;

class MusicFileWidget : public FileWidget
{
	Q_OBJECT
public:
	MusicFileWidget(MusicFile *file, QWidget *parent = nullptr);
	~MusicFileWidget();

	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();

protected:
	void mouseDoubleClicked() override;
};

