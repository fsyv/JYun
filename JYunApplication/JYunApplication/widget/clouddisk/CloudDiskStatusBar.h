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
* @brief : ��������״̬��
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/4
**/
class CloudDiskStatusBar : public QFrame
{
	Q_OBJECT
public:
	explicit CloudDiskStatusBar(QWidget *parent = nullptr);
	~CloudDiskStatusBar();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

signals:
	void selectAllChange(bool);

private:
	QFrame *m_pCheckBoxFrame;
	QCheckBox *m_pSelectAll;

	QFrame *m_pFolderFrame;
};

