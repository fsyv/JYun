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
* @brief : 文件和文件夹的父类，继承自QFrame，包括了文件样子的初始化和一些公共操作
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/21
*******************************************************************************
* @modify : 文件数据(文件对象拆分为文件数据和视图)
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/2/9
*******************************************************************************
**/

class Folder;

class FileObject : public QObject
{
	Q_OBJECT
public:
	explicit FileObject(const FileType &type = FileType::Other);
	explicit FileObject(const FileObject &file);
	virtual ~FileObject();

	//设置文件名字
	void setFileName(const QString &name);
	void clear();
	void setDateTime(QDateTime date = QDateTime::currentDateTime());
	QDateTime dateTime() const;

	//文件类型
	FileType fileType() const;
	//文件名字
	QString fileName() const;
	//文件路径
	virtual QString filePath() = 0;
	//文件名字路径
	virtual QString fileNamePath();

	//设置父类文件夹
	void setParentFolder(Folder *folder);
	Folder * parentFolder() const;

	//下载方法
	virtual bool download() = 0;
	//上传方法
	virtual bool upload() = 0;

	static FileObject *createFile(const FileType &type);

protected:
	//文件名字
	QString m_stFileName;
	FileType m_eFileType;
	//文件时间
	QDateTime m_FileDateTime;
	//父类文件夹对象
	//如果父类是根目录
	//则这个指针是它自己本身
	Folder *m_pParentFolder;
};

