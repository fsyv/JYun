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
* @brief : ��������������
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/1
**/

#include "basic\BasicWidget.h"

class CloudDiskTopWidget;
class CloudDiskLeftWidget;

class JYunCloudDisk :
	public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunCloudDisk();
	~JYunCloudDisk();

protected:
	void initWidget();

private:
	QLabel *m_pTitle;
	CloudDiskTopWidget *m_pTopWidget;
	CloudDiskLeftWidget *m_pLeftWidget;
};

