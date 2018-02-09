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
	explicit File(FileType type = FileType::Other, QListWidgetItem *item = nullptr);
	explicit File(const File &file);
	~File();

	void calcFileMd5();
	
	QString md5();

	static File *createFile(const QString &filename);

	void mouseDoubleClicked() override;
	void upload() override;
	void download() override;
	void clear() override;

protected:
	static QString fromConfigFileGetSupportSuffix(const QString &ksy);

private:
	QString m_stFileMD5;

	Folder *m_pParentFolder;
};

Q_DECLARE_METATYPE(File)