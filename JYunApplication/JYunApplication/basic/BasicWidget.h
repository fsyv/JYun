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
* @brief : ���н���Ļ�����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2017/12/28
**/

#include <QWidget>

class BasicWidget : public QWidget {
	Q_OBJECT
public:
	explicit BasicWidget(QWidget *parent = nullptr);
	virtual ~BasicWidget();

	void setStyleSheetFromFile(QString filename);

protected:
	//����Ĳ���
	virtual void widgetStyle();

	void mouseMoveEvent(QMouseEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void paintEvent(QPaintEvent *e) override;
	void resizeEvent(QResizeEvent *e) override;

	void initWidget();
	void moveWidget(const QPoint &point);
	void changeWidgetSize(const QSize &size);
	//Բ�ǽ���
	void paintRoundRect(const int &radius = 5);

public slots:
	void closeWidget();

private:
	QPushButton *m_pCloseButton;
	QPoint m_mousePressPoint;
	bool m_bMousePress;
};

