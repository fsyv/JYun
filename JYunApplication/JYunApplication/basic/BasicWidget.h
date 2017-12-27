#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>

class BasicWidget : public QWidget
{
public:
	explicit BasicWidget(QWidget *parent = nullptr);
	virtual ~BasicWidget();

	void setStyleSheetFromFile(QString filename);

protected:
	//界面的布局
	virtual void widgetStyle();

	void mouseMoveEvent(QMouseEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseReleaseEvent(QMouseEvent *e) override;
	void paintEvent(QPaintEvent *e) override;
	void resizeEvent(QResizeEvent *e) override;
};

