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
* @brief : http服务
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
	//获取头像
	void downloadHead(const QString &username);
	//上传头像
	void uploadHead(const QString &username);
	//获取头像md5
	QString getHeadMd5(const QString &username);
	//校验用户名是否存在
	bool checkUsername(const QString &username);
	//注册
	QMap<QString, QString> registered(const QString &username, const QString &userpass);
	bool modifyPass(const QString &username, const QString &userpass);
	//上传文件
	void uploadFile();
	//下载文件
	void downloadFile(const QString &md5, const QString localPath);
	//获取文件列表
	QList<FileObject *> getFileList(const QString &path);
private:
	QNetworkAccessManager *m_pManager;
	QUrl m_url;
};

