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
* @brief : 网络云盘状态栏子控件
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/24
**/

#include <QFrame>

class Folder;

class CloudDiskStatusBarChildWidget : public QFrame
{
	Q_OBJECT
public:
	enum class FolderRole {
		NotShow,		//不显示
		Root,		//根目录
		Other		//其他
	};
public:
	explicit CloudDiskStatusBarChildWidget(QWidget *parent = nullptr);
	explicit CloudDiskStatusBarChildWidget(const CloudDiskStatusBarChildWidget &child);
	~CloudDiskStatusBarChildWidget();

	void setName(const QString &name);
	void setFolderRole(const FolderRole &name);
	void setFolder(Folder *folder);

	int textWidth() const;
	FolderRole folderRole() const;
	Folder *folder() const;

protected:
	void initData();
	void initWidget();
	void adjustLabelWidth();

	void setStyleSheetFromFile(QString filename);

	void resizeEvent(QResizeEvent *e) override;
	void paintEvent(QPaintEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;

signals:
	void clicked(CloudDiskStatusBarChildWidget *);

private:
	QLabel *m_pNameLabel;

	int m_iMaxTextWidth;
	int m_iMinTextWidth;
	int m_iRriangleHight;
	int m_iTextWidth;
	FolderRole m_eRole;

	Folder *m_pCurrentFolder;
};

Q_DECLARE_METATYPE(CloudDiskStatusBarChildWidget)