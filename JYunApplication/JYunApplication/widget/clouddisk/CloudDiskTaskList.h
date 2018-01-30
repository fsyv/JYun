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
* @brief : 网络云盘上方按钮界面
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/4
**/

#include <QListWidget>

class CloudDiskTaskList : public QListWidget
{
public:
	explicit CloudDiskTaskList(QWidget *parent = nullptr);
	~CloudDiskTaskList();
};

