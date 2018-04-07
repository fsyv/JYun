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
* @brief : 文件类型
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/2/21
**/

enum class FileType
{
	Folder = 0x01,		//文件夹
	Document = 0x02,	//文档
	Image = 0x04,		//图片
	Video = 0x08,		//视频
	Music = 0x10,		//音乐
	Other = 0x20,		//其它
};