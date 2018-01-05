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
* @brief : 数据备份的列表
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/5
**/
class BackupFileListWidget : public QFrame
{
	Q_OBJECT
public:
	BackupFileListWidget(QWidget *parent = nullptr);
	~BackupFileListWidget();
};

