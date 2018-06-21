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

class File;
class FileObject;
class TaskListChild;

class CloudDiskTaskList : public QListWidget
{
	Q_OBJECT
public:
	explicit CloudDiskTaskList(QWidget *parent = nullptr);
	~CloudDiskTaskList();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	TaskListChild *getTaskChildByName(const QString &filename);

	void newTaskChild(File *file);

public slots:
	void addTask(FileObject *file);
	void uploadFile(QString filename, UploadFileMsg::QueryType type, quint16 port = 0);
	void downloadFile(QString filename, quint16 port, QString filepath);

private:
	QList<File *> m_tasks;
};

