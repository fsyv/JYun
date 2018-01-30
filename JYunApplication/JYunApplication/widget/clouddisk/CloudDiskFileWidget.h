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
	//����
	void sortItems();

public slots:
	//ȫѡ��ť��Ӧ����
	void selectAllClick(bool flag);
	//�ļ���ʾ����
	void fileCategory(int echo);

private:
	QList<FileObject *> *m_pFileList;
};

