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
* @brief : 网络云盘上方按钮界面
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/4
**/

class CloudDiskTopWidget : public QFrame
{
	Q_OBJECT
public:
	explicit CloudDiskTopWidget(QWidget *parent = nullptr);
	~CloudDiskTopWidget();

	void setStyleSheetFromFile(QString filename);
protected:
	void initWidget();

private:
	QPushButton *m_pUpload;
	QPushButton *m_pBackward;
	QPushButton *m_pForward;
	QPushButton *m_pRefresh; 
	QPushButton *m_pDownload;
	QPushButton *m_pShare;
	QPushButton *m_pTaskList;
};
