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
* @brief : 提示框的基类
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/9
**/

#include <QDialog>

class BasicMessageBox : public QDialog
{
	Q_OBJECT
public:
	explicit BasicMessageBox(QWidget *parent = nullptr);
	~BasicMessageBox();

	void setStyleSheetFromFile(QString filename);

protected:
	void mouseMoveEvent(QMouseEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;

	void moveWidget(const QPoint &point);
	void changeWidgetSize(const QSize &size);
	//圆角界面
	void paintRoundRect(const int &radius = 5);

private:
	QPoint m_mousePressPoint;
	bool m_bMousePress;
};

