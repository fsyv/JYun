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
* @brief : 其它文件类
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/22
**/

#include "File.h"

class OtherFile : public File
{
public:
	OtherFile(Folder *parent = nullptr);
	~OtherFile();

	bool preview() override;
};

