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
* @brief : �ĵ��ļ���
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/22
**/

#include "File.h"

class DocumentFile : public File
{
	Q_OBJECT
public:
	explicit DocumentFile(QListWidgetItem *item = nullptr);
	~DocumentFile();

	void initMenu();
	void initWidget();
	void conn();
	void initData();
	void init();

	static bool isDocumentFile(const QString &fileSuffix);

protected:
	void mouseDoubleClicked() override;
};

