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
	explicit Folder();
	explicit Folder(const Folder &folder);
	~Folder();

	void setAbsolutePath(const Folder &folder);
	void setAbsolutePath(const QString &absolutePath);

	//����ļ�
	void addFile(FileObject *file);

	QList<FileObject *> *fileList();
	QList<FileObject *> dumpFileLists(const QByteArray &byte);
	QByteArray filesToJson();
	QString absolutePath() const;
	//��ȡ��Ŀ¼
	Folder *getRootFolder();
	//ֱ��ˢ�£�������1����2������ȡ����
	void update();
	QDateTime refreshDateTime() const;

	//�ļ�·��
	QString filePath() final;

	bool download() final;
	bool upload() final;
	//ɾ������
	bool deleted() final;
	bool delect(FileObject *file);
	bool rename(QString name) final;
	bool uploadFils();

	//������Ŀ¼
	static Folder *createRootFolder(const QString &username);

signals:
	void task(FileObject *, bool);

protected:
	void init();
	//�Ƿ���Ҫˢ���б�
	bool isRefresh();
	//һ�������ȡ��ʽ
	void refresh();
	//���������ȡ��ʽ
	QList<FileObject *> getFilesFromLocal();
	//�����������
	void cacheFilesToLocal();
	void cacheFilesToLocal(const QByteArray &byte);
	//���������Ƿ���Ч
	bool isLocalCacheValid();
	//���������ȡ��ʽ
	QList<FileObject *> getFilesFromServer();
	//����
	void sortFiles(QList<FileObject *> &files);

private:
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