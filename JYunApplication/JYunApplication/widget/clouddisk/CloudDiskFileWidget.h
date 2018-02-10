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

class FileObjectWidget;

class File;
class Folder;

class CloudDiskFileWidget: public QListWidget
{
	Q_OBJECT
public:
	explicit CloudDiskFileWidget(QWidget *parent = nullptr);
	~CloudDiskFileWidget();

	//在完成信号槽绑定后，执行的函数
	void afterConn();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	void showCategory(int echo);
	void showAll();
	//设置当前文件夹
	void setFolder(Folder *folder);
	//更新当前显示内容
	void update();
	QList<QListWidgetItem *> items();

public slots:
	//全选按钮响应函数
	void selectAllClick(bool flag);
	//文件显示分类
	void fileCategory(int echo);
	//上传文件响应函数
	void uploadFile(File *file);
	//后退响应函数
	void backward();
	//向前响应函数
	void forward();
	//刷新响应函数
	void refresh();
	//下载文件响应函数
	void downloadFile();
	//分享文件响应函数
	void shareFile();
	//文件夹打开
	void openFolder(Folder *folder);
	//状态栏栏按钮点击
	void stateBarFolderClicked(Folder *folder);
	//显示根目录
	void showRootDirectory();

signals:
	void enterFolder(Folder *folder);

private:
	Folder *m_pCurrentFolder;
	QQueue<Folder *> m_FolderQueue;
};

