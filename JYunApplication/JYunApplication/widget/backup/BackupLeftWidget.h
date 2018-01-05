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
* @brief : 数据备份左边按钮
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/4
**/

class BackupLeftWidget : public QFrame
{
	Q_OBJECT
public:
	explicit BackupLeftWidget(QWidget *parent = nullptr);
	~BackupLeftWidget();
protected:
	void initWidget();

private:
	QPushButton *m_pRootDirectory;
	QPushButton *m_pDelete;
	QPushButton *m_pShare;

	QFrame *m_pSortFrame;
	QPushButton *m_pDocument;
	QPushButton *m_pPicture;
	QPushButton *m_pVideo;
	QPushButton *m_pMusic;

	QPushButton *m_pSetup;
};

