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
* @brief : 文件夹类
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

	//添加文件
	void addFile(FileObject *file);

	QList<FileObject *> *fileList();
	QList<FileObject *> dumpFileLists(const QByteArray &byte);
	QByteArray filesToJson();
	QString absolutePath() const;
	//获取根目录
	Folder *getRootFolder();
	//直接刷新，跳过从1级，2级缓存取数据
	void update();
	QDateTime refreshDateTime() const;

	//文件路径
	QString filePath() final;

	bool download() final;
	bool upload() final;
	//删除方法
	bool deleted() final;
	bool delect(FileObject *file);
	bool rename(QString name) final;
	bool uploadFils();

	//创建根目录
	static Folder *createRootFolder(const QString &username);

signals:
	void task(FileObject *, bool);

protected:
	void init();
	//是否需要刷新列表
	bool isRefresh();
	//一级缓存获取方式
	void refresh();
	//二级缓存获取方式
	QList<FileObject *> getFilesFromLocal();
	//保存二级缓存
	void cacheFilesToLocal();
	void cacheFilesToLocal(const QByteArray &byte);
	//二级缓存是否有效
	bool isLocalCacheValid();
	//三级缓存获取方式
	QList<FileObject *> getFilesFromServer();
	//排序
	void sortFiles(QList<FileObject *> &files);

private:
	//当前文件夹下文件和文件夹列表
	//当前文件夹列表总共有三级缓存
	// 一级缓存：从内存中获取（有效时间4个小时）
	// 二级缓存：从本地磁盘中获取（有效时间24个小时）
	// 三级缓存：从服务器获取（有效时间永久-_-||）
	QList<FileObject *> *m_pFileLists;
	//刷新时间
	QDateTime m_RefreshDateTime;
	//文件夹的绝对路径
	//"username:path"形式
	QString m_stAbsolutePath;
};

Q_DECLARE_METATYPE(Folder)