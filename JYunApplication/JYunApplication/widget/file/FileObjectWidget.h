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
* @brief : �ļ����ļ��еĸ��࣬�̳���QFrame���������ļ����ӵĳ�ʼ����һЩ��������
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/21
*******************************************************************************
* @modify : �ļ���ͼ(�ļ�������Ϊ�ļ����ݺ���ͼ)
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
	//����ͼƬ��ʾ����
	void setPicture(const QString &resource);
	//�����ļ�����ʾ
	void setNameLabel(const QString &name);
	//����CheckBox��ť״̬
	void setConfirmCheckBoxStatus(bool status);

	FileObject *file() const;

	//����
	virtual void copy();
	//�ƶ�
	virtual void move();
	//������
	virtual void rename();
	//�ϴ�
	virtual void upload();
	//����
	virtual void download();
	//���
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

	//�������ĵ���¼���Ӧ����
	virtual void mouseLeftClicked();
	//����Ҽ��ĵ���¼���Ӧ����
	virtual void mouseRightClicked();
	//���˫���¼���Ӧ����
	virtual void mouseDoubleClicked() = 0;

	QCheckBox *m_pConfirmCheckBox;
	QLabel *m_pPictureLabel;
	QLabel *m_pNameLabel;
	//�Ҽ��˵�
	QMenu *m_pMenu;

	FileObject *m_pFile;
};

