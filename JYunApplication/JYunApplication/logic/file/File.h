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
* @brief : 所有文件的公共类，文件总共分为：1.文档；2.图片；3.视频；4音乐；5.其它
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
	//移除本地文件
	bool remove();

	//文件路径
	virtual QString filePath() final;

	bool download() final;
	//增
	bool upload() final;
	//删
	bool deleted() final;
	//改
	bool rename(QString name) final;

	void pause();
	void restart();

	//文件的预览方法
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
	//文件大小
	quint64 m_ui64FileSize;

	//远程文件定位
	QUrl m_urlRemote;
	//本地文件定位
	QUrl m_urlLocal;

	QNetworkReply *m_pReply;
	QNetworkAccessManager * m_pManager;
	QFile *m_pFile;
	TaskType m_eTaskType;
};

Q_DECLARE_METATYPE(File)