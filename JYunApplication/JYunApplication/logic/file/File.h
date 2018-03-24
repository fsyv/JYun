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
* @brief : 所有文件的公共类，文件总共分为：1.文档；2.图片；3.视频；4音乐；5.其它
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/21
**/

#include "FileObject.h"

class Folder;

class File : public FileObject
{
	Q_OBJECT
public:
	explicit File(const FileType &type = FileType::Other);
	explicit File(const File &file);
	~File();

	void calcFileMd5();
	void setParentFolder(Folder *folder);
	void setFileSize(quint64 size);
	void setUploadDateTime(QDateTime time = QDateTime::currentDateTime());
	void clear();

	QString md5();
	Folder *parentFolder() const;
	quint64 fileSize() const;
	QDateTime uploadDateTime() const;

	static File *createFile(const QString &filename);

protected:
	static QString fromConfigFileGetSupportSuffix(const QString &ksy);

private:
	QString m_stFileMD5;
	//文件大小
	quint64 m_ui64FileSize;
	//文件上传时间
	QDateTime m_uploadDateTime;

	//当前文件所在的文件夹
	Folder *m_pParentFolder;
};

Q_DECLARE_METATYPE(File)