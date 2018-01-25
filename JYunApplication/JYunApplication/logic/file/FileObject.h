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
**/

#include<QFrame>

class QListWidgetItem;

class FileObject : public QFrame
{
	Q_OBJECT
public:
	enum class FileType {
		Folder = 0,		//�ļ���
		Document,		//�ĵ�
		Image,			//ͼƬ
		Video,			//��Ƶ
		Music,			//����
		Other,			//����
	};
public:
	explicit FileObject(QListWidget *parent = nullptr);
	explicit FileObject(QString name, FileType type, QListWidget *parent = nullptr);
	virtual ~FileObject();

	void setStyleSheetFromFile(QString filename);
	//����ͼƬ��ʾ����
	void setPicture(const QString &resource);
	//�����ļ�����ʾ
	void setNameLabel(const QString &name);
	//�����ļ�����
	void setFileName(const QString &name);
	//�����ļ�·��
	void setFilePath(const QString &path);
	//����CheckBox��ť״̬
	void setConfirmCheckBoxStatus(bool status);
	//�ļ�����
	FileType fileType() const;
	//��ͼitem
	QListWidgetItem *item() const;
	//�ļ�����
	QString fileName() const;
	//�ļ�·��
	QString filePath() const;
	//�ļ�����·��
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

	//�������ĵ���¼���Ӧ����
	virtual void mouseLeftClicked();
	//����Ҽ��ĵ���¼���Ӧ����
	virtual void mouseRightClicked();
	//���˫���¼���Ӧ����
	virtual void mouseDoubleClicked() = 0;

	QCheckBox *m_pConfirmCheckBox;
	QLabel *m_pPictureLabel;
	QLabel *m_pNameLabel;
	QListWidgetItem *m_pListWidgetItem;

	//�ļ�����
	QString m_stFileName;
	FileType m_eFileType;
	//����·��
	QString m_stFilePath;
	//�Ҽ��˵�
	QMenu *m_pMenu;
};

