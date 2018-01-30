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

#include <QList>

class FileObject;

class CloudDiskFileWidget: public QListWidget
{
	Q_OBJECT
public:
	explicit CloudDiskFileWidget(QWidget *parent = nullptr);
	~CloudDiskFileWidget();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	void showCategory(int echo);
	void showAll();
	//排序
	void sortItems();

public slots:
	//全选按钮响应函数
	void selectAllClick(bool flag);
	//文件显示分类
	void fileCategory(int echo);

private:
	QList<FileObject *> *m_pFileList;
};

