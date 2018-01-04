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
* @brief : 主界面（功能选择）
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2017/12/31
**/

#include "basic/BasicWidget.h"

#include <QWidget>

class JYunApplication : public BasicWidget
{
	Q_OBJECT
public:
	explicit JYunApplication(BasicWidget *parent = Q_NULLPTR);
	~JYunApplication();

protected:
	void initWidget();

	void resizeEvent(QResizeEvent *e) override;
	void setAvatar(const  QPixmap &pixmap);

private:
	QPushButton *m_pSetupButton;
	QPushButton *m_pCloudDiskButton;
	QPushButton *m_pBackupButton;
};
