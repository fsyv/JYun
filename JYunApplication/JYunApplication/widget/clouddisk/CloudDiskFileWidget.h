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

class File;
class Folder;
class FileObject;
class FileObjectWidget;

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
	void initMenu();
	void init();

	//���õ�ǰ�ļ���
	void setFolder(Folder *folder);
	//���µ�ǰ��ʾ����
	void update();
	QList<QListWidgetItem *> items();

	void contextMenuEvent(QContextMenuEvent *e) override;
	FileObjectWidget* newFileWidget(FileObject *file);

public slots:
	//ȫѡ��ť��Ӧ����
	void selectAllClick(bool flag);
	//�ļ���ʾ����
	void fileCategory(int echo);
	//�ϴ��ļ���Ӧ����
	void uploadFile(File *file);
	//������Ӧ����
	void backward();
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
	//
	void fileDoubleClick(FileObject *file);

	//�Ҽ��˵�����Ӧ�¼�
	//�½��ļ���
	void newFolder();
	//�ϴ��ļ�
	void upload();
	//����
	void share();

	//�ļ���ͼ��Ӧ
	void delect();

signals:
	void enterFolder(Folder *folder);
	void task(FileObject *, bool);

private:
	QMenu *m_pMenu;

	Folder *m_pCurrentFolder;
	QQueue<Folder *> m_FolderQueue;
	int m_iEcho;
};

