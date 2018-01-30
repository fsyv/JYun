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
* @brief : �����ļ��Ĺ����࣬�ļ��ܹ���Ϊ��1.�ĵ���2.ͼƬ��3.��Ƶ��4���֣�5.����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/21
**/

#include "FileObject.h"

class File : public FileObject
{
	Q_OBJECT
public:
	explicit File(QString name, FileType type, QListWidget *parent = nullptr);
	~File();

	void calcFileMd5();
	
	QString md5();

private:
	QString m_stFileMD5;
};
