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
* @brief : ���������ļ�չʾ����
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

	//������źŲ۰󶨺�ִ�еĺ���
	void afterConn();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	void showCategory(int echo);
	void showAll();
	//���õ�ǰ�ļ���
	void setFolder(Folder *folder);
	//���µ�ǰ��ʾ����
	void update();
	QList<QListWidgetItem *> items();

public slots:
	//ȫѡ��ť��Ӧ����
	void selectAllClick(bool flag);
	//�ļ���ʾ����
	void fileCategory(int echo);
	//�ϴ��ļ���Ӧ����
	void uploadFile(File *file);
	//������Ӧ����
	void backward();
	//��ǰ��Ӧ����
	void forward();
	//ˢ����Ӧ����
	void refresh();
	//�����ļ���Ӧ����
	void downloadFile();
	//�����ļ���Ӧ����
	void shareFile();
	//�ļ��д�
	void openFolder(Folder *folder);
	//״̬������ť���
	void stateBarFolderClicked(Folder *folder);
	//��ʾ��Ŀ¼
	void showRootDirectory();

signals:
	void enterFolder(Folder *folder);

private:
	Folder *m_pCurrentFolder;
	QQueue<Folder *> m_FolderQueue;
};

