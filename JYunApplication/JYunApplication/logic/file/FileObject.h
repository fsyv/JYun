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
		Folder = 0x01,		//文件夹
		Document = 0x02,		//文档
		Image	 = 0x04,		//图片
		Video	 = 0x08,		//视频
		Music	 = 0x10,		//音乐
		Other	 = 0x20,		//其它
	};
public:
	explicit FileObject(QListWidgetItem *item = nullptr);
	explicit FileObject(FileType type, QListWidgetItem *item = nullptr);
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
	//设置文件名字+路径
	void setFileNamePath(const QString &namePath);
	//设置CheckBox按钮状态
	void setConfirmCheckBoxStatus(bool status);
	//设置视图item
	void setItem(QListWidget *parent);
	void setItem(QListWidgetItem *item);

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

	//复制
	virtual void copy();
	//移动
	virtual void move();
	//重命名
	virtual void rename();
	//上传
	virtual void upload();
	//下载
	virtual void download();
	//清空
	virtual void clear();

	static FileObject *createFile(const FileType &type);

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

