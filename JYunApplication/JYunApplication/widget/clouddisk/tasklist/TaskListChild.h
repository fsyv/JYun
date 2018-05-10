#pragma once
#include <QWidget>


class TaskListChild : public QWidget
{
    Q_OBJECT
public:
    TaskListChild(QWidget *parent = 0);
    ~TaskListChild();
	void init();
	void setLabelName(QString name);
	void setStyleSheetFromFile(QString filename);

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void loadProgress(qint64 current, qint64 total);

signals:
	void clicked(bool b);

private:
    QPixmap backGround;
    int userdVaule;
    int currentValue;

    QLabel *m_pName;
    QPushButton *m_pButton;
};

