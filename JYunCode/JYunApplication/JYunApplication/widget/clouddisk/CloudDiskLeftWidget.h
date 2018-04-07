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
* @brief : 网络云盘左方按钮界面
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/4
**/

class CloudDiskLeftWidget : public QFrame
{
	Q_OBJECT
public:
	explicit CloudDiskLeftWidget(QWidget *parent = nullptr);
	~CloudDiskLeftWidget();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

protected slots:
	void documentButtonClick(bool flag);
	void pictureButtonClick(bool flag);
	void videoButtonClick(bool flag);
	void musicButtonClick(bool flag);

signals:
	void rootClicked();
	void recentlyClicked(bool);
	void fileEchoChange(int);
	void setupClicked(bool);

private:
	QPushButton *m_pRootDirectory;
	QPushButton *m_pRecently;

	QFrame *m_pSortFrame;
	QPushButton *m_pDocument;
	QPushButton *m_pPicture;
	QPushButton *m_pVideo;
	QPushButton *m_pMusic;

	QPushButton *m_pSetup;

	int m_iCurrentFileStyle;
};

