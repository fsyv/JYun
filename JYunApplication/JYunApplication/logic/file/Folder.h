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
	explicit Folder(QListWidgetItem *parent = nullptr);
	explicit Folder(const Folder &folder);
	~Folder();

	void setAbsolutePath(const Folder &folder);
	void setAbsolutePath(const QString &absolutePath);
	//设置父类文件夹
	void setParentFolder(Folder *parent);

	Folder * parentFolder() const;
	QList<FileObject *> *fileList();
	QString absolutePath() const;
	//获取根目录
	Folder *getRootFolder();
	//直接刷新，跳过从1级，2级缓存取数据
	void update();

	//创建根目录
	static Folder *createRootFolder(const QString &username);

protected:
	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();
	//是否需要刷新列表
	bool isRefresh();
	//一级缓存获取方式
	void refresh();
	//二级缓存获取方式
	QList<FileObject *> getFilesFromLocal();
	//保存二级缓存
	void cacheFilesToLocal();
	//二级缓存是否有效
	bool isLocalCacheValid();
	//三级缓存获取方式
	QList<FileObject *> getFilesFromServer();
	//排序
	void sortFiles(QList<FileObject *> &files);
	//文件列表信号槽绑定
	void connFiles(QList<FileObject *> &files);

	void mouseDoubleClicked() override;

protected slots:
	void openFolder(Folder *folder);

signals:
	void open(Folder *);

private:
	//父类文件夹对象
	//如果父类是根目录
	//则这个指针是它自己本身
	Folder *m_pParentFolder;
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