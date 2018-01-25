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
* @brief : 文件和文件夹的父类，继承自QFrame，包括了文件样子的初始化和一些公共操作
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/21
**/

#include<QFrame>

class QListWidgetItem;

class FileObject : public QFrame
{
	Q_OBJECT
public:
	enum class FileType {
		Folder = 0,		//文件夹
		Document,		//文档
		Image,			//图片
		Video,			//视频
		Music,			//音乐
		Other,			//其它
	};
public:
	explicit FileObject(QListWidget *parent = nullptr);
	explicit FileObject(QString name, FileType type, QListWidget *parent = nullptr);
	virtual ~FileObject();

	void setStyleSheetFromFile(QString filename);
	//设置图片显示类容
	void setPicture(const QString &resource);
	//设置文件名显示
	void setNameLabel(const QString &name);
	//设置文件名字
	void setFileName(const QString &name);
	//设置文件路径
	void setFilePath(const QString &path);
	//设置CheckBox按钮状态
	void setConfirmCheckBoxStatus(bool status);
	//文件类型
	FileType fileType() const;
	//视图item
	QListWidgetItem *item() const;
	//文件名字
	QString fileName() const;
	//文件路径
	QString filePath() const;
	//文件名字路径
	QString fileNamePath() const;
protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	void destroyWidget();
	void destroyItem();

	void enterEvent(QEvent *e) override;
	void leaveEvent(QEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseDoubleClickEvent(QMouseEvent *e) override;

	//鼠标左键的点击事件响应函数
	virtual void mouseLeftClicked();
	//鼠标右键的点击事件响应函数
	virtual void mouseRightClicked();
	//鼠标双击事件响应函数
	virtual void mouseDoubleClicked() = 0;

	QCheckBox *m_pConfirmCheckBox;
	QLabel *m_pPictureLabel;
	QLabel *m_pNameLabel;
	QListWidgetItem *m_pListWidgetItem;

	//文件名字
	QString m_stFileName;
	FileType m_eFileType;
	//本地路径
	QString m_stFilePath;
	//右键菜单
	QMenu *m_pMenu;
};

