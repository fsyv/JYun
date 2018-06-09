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
* @brief : �����ļ��Ĺ����࣬�ļ��ܹ���Ϊ��1.�ĵ���2.ͼƬ��3.��Ƶ��4���֣�5.����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/21
**/

#include "FileObject.h"

class Folder;

class File : public FileObject
{
	Q_OBJECT
public:
	enum TaskType{
		Download,
		Upload
	};

	explicit File(const FileType &type = FileType::Other, Folder *parent = nullptr);
	explicit File(const File &file);
	~File();

	void calcFileMd5();
	void setFileSize(quint64 size);
	void clear();
	void setMd5(QString md5);

	QString md5();
	Folder *parentFolder() const;
	quint64 fileSize() const;

	void getRemoteUrl();
	void setRemoteUrl(QString url);
	void setRemoteUrl(QString host, quint16 port, QString path);
	QUrl remoteUrl();

	void setLocalUrl(QString path);
	QUrl localUrl();
	//�Ƴ������ļ�
	bool remove();

	//�ļ�·��
	virtual QString filePath() final;

	bool download() final;
	//��
	bool upload() final;
	//ɾ
	bool deleted() final;
	//��
	bool rename(QString name) final;

	void pause();
	void restart();

	//�ļ���Ԥ������
	virtual bool preview();

	static File *createFile(const QString &filename, Folder *parent = nullptr);

protected:
	static QString fromConfigFileGetSupportSuffix(const QString &ksy);

protected slots:
	void readContent();
	void replyFinished(QNetworkReply *reply);
	void loadError(QNetworkReply::NetworkError);

public slots:
	void taskStatus(bool b);

signals:
	void loadProgress(qint64, qint64);
	void finished();

private:
	QString m_stFileMD5;
	//�ļ���С
	quint64 m_ui64FileSize;

	//Զ���ļ���λ
	QUrl m_urlRemote;
	//�����ļ���λ
	QUrl m_urlLocal;

	QNetworkReply *m_pReply;
	QNetworkAccessManager * m_pManager;
	QFile *m_pFile;
	TaskType m_eTaskType;
};

Q_DECLARE_METATYPE(File)