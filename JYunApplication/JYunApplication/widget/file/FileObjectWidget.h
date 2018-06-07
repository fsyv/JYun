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

	bool getConfirmCheckBoxStatus();

	FileObject *file() const;

	//������
	virtual void rename();
	//�ϴ�
	virtual void upload();
	//����
	virtual void download();
	//ɾ��
	virtual void deleted();
	//���
	virtual void clear();
	//����
	virtual void share();
	//����
	virtual void copy();
	//����
	virtual void cut();

	static FileObjectWidget *createWidget(FileObject *file);

signals:
	void doubleClick(FileObject *);
	void delect();
	void shared();
	void downloadd();
	void uploadd();

protected:
	void initWidget();
	void conn();
	void initData();
	void init();

	void destroyWidget();
	//�������������õ�����
	void nameInputFocusIn();
	//������������ʧȥ����
	void nameInputFocusOut();

	void enterEvent(QEvent *e) override;
	void leaveEvent(QEvent *e) override;
	void mousePressEvent(QMouseEvent *e) override;
	void mouseDoubleClickEvent(QMouseEvent *e) override;

	//�������ĵ���¼���Ӧ����
	virtual void mouseLeftClicked();
	//����Ҽ��ĵ���¼���Ӧ����
	virtual void mouseRightClicked();
	//���˫���¼���Ӧ����
	virtual void mouseDoubleClicked();
	//��д�����¼�������
	bool eventFilter(QObject *object, QEvent *e) override;

	QCheckBox *m_pConfirmCheckBox;
	QLabel *m_pPictureLabel;
	QLabel *m_pNameLabel;
	QLineEdit *m_pNameInput;
	//�Ҽ��˵�
	QMenu *m_pMenu;

	FileObject *m_pFile;
};

