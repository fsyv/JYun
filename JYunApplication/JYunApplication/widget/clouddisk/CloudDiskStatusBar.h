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

class Folder;
class CloudDiskStatusBarChildWidget;

class CloudDiskStatusBar : public QFrame
{
	Q_OBJECT
public:
	explicit CloudDiskStatusBar(QWidget *parent = nullptr);
	~CloudDiskStatusBar();

public slots:
	void addFolder(Folder *folder);
	void childWidgetClicked(CloudDiskStatusBarChildWidget *child);

protected:
	void initWidget();
	void conn();
	void initData();
	void init();
	void adjustFolderWidth();

signals:
	void selectAllChange(bool);
	void folderClicked(Folder *);

private:
	QFrame *m_pCheckBoxFrame;
	QCheckBox *m_pSelectAll;

	QFrame *m_pFolderFrame;

	QList<CloudDiskStatusBarChildWidget *> m_FolderList;

	const int MAX_WIDTH = 660;
};

