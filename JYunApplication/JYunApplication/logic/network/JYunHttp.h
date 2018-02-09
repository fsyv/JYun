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
* @brief : http����
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/8
**/

class FileObject;

class JYunHttp : public QObject
{
	Q_OBJECT
public:
	explicit JYunHttp();
	virtual ~JYunHttp();

	QMap<QString, QString> login(const QString &username, const QString &userpass);
	//��ȡͷ��
	void downloadHead(const QString &username);
	//�ϴ�ͷ��
	void uploadHead(const QString &username);
	//��ȡͷ��md5
	QString getHeadMd5(const QString &username);
	//У���û����Ƿ����
	bool checkUsername(const QString &username);
	//ע��
	QMap<QString, QString> registered(const QString &username, const QString &userpass);
	bool modifyPass(const QString &username, const QString &userpass);
	//�ϴ��ļ�
	void uploadFile();
	//�����ļ�
	void downloadFile(const QString &md5, const QString localPath);
	//��ȡ�ļ��б�
	QList<FileObject *> getFileList(const QString &path);
private:
	QNetworkAccessManager *m_pManager;
	QUrl m_url;
};

