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
* @brief : �ļ�����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/21
**/

#include "FileObject.h"

class Folder : public FileObject
{
	Q_OBJECT
public:
	explicit Folder(QListWidgetItem *parent = nullptr);
	explicit Folder(const Folder &folder);
	~Folder();

	void setAbsolutePath(const Folder &folder);
	void setAbsolutePath(const QString &absolutePath);
	//���ø����ļ���
	void setParentFolder(Folder *parent);

	Folder * parentFolder() const;
	QList<FileObject *> *fileList();
	QString absolutePath() const;
	//��ȡ��Ŀ¼
	Folder *getRootFolder();
	//ֱ��ˢ�£�������1����2������ȡ����
	void update();

	//������Ŀ¼
	static Folder *createRootFolder(const QString &username);

protected:
	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();
	//�Ƿ���Ҫˢ���б�
	bool isRefresh();
	//һ�������ȡ��ʽ
	void refresh();
	//���������ȡ��ʽ
	QList<FileObject *> getFilesFromLocal();
	//�����������
	void cacheFilesToLocal();
	//���������Ƿ���Ч
	bool isLocalCacheValid();
	//���������ȡ��ʽ
	QList<FileObject *> getFilesFromServer();
	//����
	void sortFiles(QList<FileObject *> &files);
	//�ļ��б��źŲ۰�
	void connFiles(QList<FileObject *> &files);

	void mouseDoubleClicked() override;

protected slots:
	void openFolder(Folder *folder);

signals:
	void open(Folder *);

private:
	//�����ļ��ж���
	//��������Ǹ�Ŀ¼
	//�����ָ�������Լ�����
	Folder *m_pParentFolder;
	//��ǰ�ļ������ļ����ļ����б�
	//��ǰ�ļ����б��ܹ�����������
	// һ�����棺���ڴ��л�ȡ����Чʱ��4��Сʱ��
	// �������棺�ӱ��ش����л�ȡ����Чʱ��24��Сʱ��
	// �������棺�ӷ�������ȡ����Чʱ������-_-||��
	QList<FileObject *> *m_pFileLists;
	//ˢ��ʱ��
	QDateTime m_RefreshDateTime;
	//�ļ��еľ���·��
	//"username:path"��ʽ
	QString m_stAbsolutePath;
};

Q_DECLARE_METATYPE(Folder)