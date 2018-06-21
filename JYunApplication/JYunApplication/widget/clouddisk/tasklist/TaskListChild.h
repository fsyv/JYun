#pragma once
#include <QWidget>

class File;
class FileProcess;

class TaskListChild : public QWidget
{
    Q_OBJECT
public:
    TaskListChild(QWidget *parent = 0);
    ~TaskListChild();
	void initWidget();
	void conn();
	void initData();
	void init();
	void setLabelName(QString name);
	void setStyleSheetFromFile(QString filename);
	void setFile(File *file);
	void setPort(quint16 port);
	void start();
	void pause();
	void stop();
	void finished();
	void setFilePath(QString path);

protected:
    void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);

	void fileProcess();

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

	File *m_pFile;
	FileProcess *m_pFileProcess;
	int m_iTimer;
};

