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


class FileObject : public QObject
{
	Q_OBJECT
public:
	explicit FileObject(const FileType &type = FileType::Other);
	explicit FileObject(const FileObject &file);
	virtual ~FileObject();

	//设置文件名字
	void setFileName(const QString &name);
	//设置文件路径
	void setFilePath(const QString &path);
	//设置文件名字+路径
	void setFileNamePath(const QString &namePath);
	void clear();


	//文件类型
	FileType fileType() const;
	//文件名字
	QString fileName() const;
	//文件路径
	QString filePath() const;
	//文件名字路径
	QString fileNamePath() const;

	static FileObject *createFile(const FileType &type);

protected:
	void init();

	//文件名字
	QString m_stFileName;
	FileType m_eFileType;
	//本地路径
	QString m_stFilePath;
};

