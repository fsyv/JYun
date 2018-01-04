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
* @brief : ÍøÂçÔÆÅÌ×´Ì¬À¸
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/4
**/
class CloudDiskStatusBar : public QFrame
{
public:
	explicit CloudDiskStatusBar(QWidget *parent = nullptr);
	~CloudDiskStatusBar();

protected:
	void initWidget();

private:
	QFrame *m_pCheckBoxFrame;
	QCheckBox *m_pSelectAll;
};

