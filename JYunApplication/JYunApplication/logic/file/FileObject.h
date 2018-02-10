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
* @modify : �ļ�����(�ļ�������Ϊ�ļ����ݺ���ͼ)
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/2/9
*******************************************************************************
**/


class FileObject : public QObject
{
	Q_OBJECT
public:
	explicit FileObject(const FileType &type = FileType::Other);
	explicit FileObject(const FileObject &file);
	virtual ~FileObject();

	//�����ļ�����
	void setFileName(const QString &name);
	//�����ļ�·��
	void setFilePath(const QString &path);
	//�����ļ�����+·��
	void setFileNamePath(const QString &namePath);
	void clear();


	//�ļ�����
	FileType fileType() const;
	//�ļ�����
	QString fileName() const;
	//�ļ�·��
	QString filePath() const;
	//�ļ�����·��
	QString fileNamePath() const;

	static FileObject *createFile(const FileType &type);

protected:
	void init();

	//�ļ�����
	QString m_stFileName;
	FileType m_eFileType;
	//����·��
	QString m_stFilePath;
};

