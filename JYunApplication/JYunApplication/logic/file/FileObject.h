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

class Folder;

class FileObject : public QObject
{
	Q_OBJECT
public:
	explicit FileObject(const FileType &type = FileType::Other, Folder *parent = nullptr);
	explicit FileObject(const FileObject &file);
	virtual ~FileObject();

	//�����ļ�����
	void setFileName(const QString &name);
	void clear();
	void setDateTime(QDateTime date = QDateTime::currentDateTime());
	QDateTime dateTime() const;

	//�ļ�����
	FileType fileType() const;
	//�ļ�����
	QString fileName() const;
	//�ļ�·��
	virtual QString filePath() = 0;
	//�ļ�����·��
	virtual QString fileNamePath();

	//���ø����ļ���
	void setParentFolder(Folder *folder);
	Folder * parentFolder() const;

	//���ط���
	virtual bool download() = 0;
	//�ϴ�����
	virtual bool upload() = 0;
	//ɾ������
	virtual bool deleted() = 0;
	//��������
	virtual bool rename(QString name) = 0;

	static FileObject *createFile(const FileType &type, Folder *parent = nullptr);

signals:
	void fileStatusChange(FileObject *);

protected:
	//�ļ�����
	QString m_stFileName;
	FileType m_eFileType;
	//�ļ�ʱ��
	QDateTime m_FileDateTime;
	//�����ļ��ж���
	//��Ŀ¼�ĸ���Ϊnullptr
	Folder *m_pParentFolder;
};

