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
*******************************************************************************
* @modify : 文件视图(文件对象拆分为文件数据和视图)
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/2/9
*******************************************************************************
**/

#include <QFrame>

class FileObject;

class FileObjectWidget : public QFrame
{
	Q_OBJECT
public:
	explicit FileObjectWidget(FileObject *file, QWidget *parent = nullptr);
	virtual ~FileObjectWidget();

	void setStyleSheetFromFile(QString filename);
	//设置图片显示类容
	void setPicture(const QString &resource);
	//设置文件名显示
	void setNameLabel(const QString &name);
	//设置CheckBox按钮状态
	void setConfirmCheckBoxStatus(bool status);

	FileObject *file() const;

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

	static FileObjectWidget *createWidget(FileObject *file);

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	void destroyWidget();

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
	//右键菜单
	QMenu *m_pMenu;

	FileObject *m_pFile;
};

