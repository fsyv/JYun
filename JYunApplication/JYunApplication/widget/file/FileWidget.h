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
* @brief : �����ļ��Ĺ����࣬�ļ��ܹ���Ϊ��1.�ĵ���2.ͼƬ��3.��Ƶ��4���֣�5.����
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