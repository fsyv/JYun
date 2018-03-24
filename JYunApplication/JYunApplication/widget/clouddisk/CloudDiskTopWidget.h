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

class File;

class CloudDiskTopWidget : public QFrame
{
	Q_OBJECT
public:
	explicit CloudDiskTopWidget(QWidget *parent = nullptr);
	~CloudDiskTopWidget();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

protected slots:
    //上传按钮响应函数
	void upload();

signals:
	void uploadFile(File *);
	void backward();
	void refresh();
	void downloadFile();
	void shareFile();
	void taskListButtonClicked(bool);

private:
	QPushButton *m_pUpload;
	QPushButton *m_pBackward;
	QPushButton *m_pRefresh; 
	QPushButton *m_pDownload;
	QPushButton *m_pShare;
	QPushButton *m_pTaskList;
};
