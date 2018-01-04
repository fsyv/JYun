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
* @brief : 网络云盘文件展示界面
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/4
**/
class CloudDiskFileWidget: public QFrame
{
	Q_OBJECT
public:
	explicit CloudDiskFileWidget(QWidget *parent = nullptr);
	~CloudDiskFileWidget();

protected:
	void initWidget();
};

