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
* @brief : 自定义关闭按钮
* @author : fsyv
* @email : fsyv@qq.com
* @date : 2017/12/28
**/

class CloseButton : public QLabel {
	Q_OBJECT
public:
	explicit CloseButton(QWidget *parent = nullptr);
	virtual ~CloseButton();

private:
	void mouseMoveEvent(QMouseEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void enterEvent(QEvent *e) override;
	void leaveEvent(QEvent *e) override;

	bool m_bFlat;

signals:
	void click();
};
