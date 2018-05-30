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
* @brief : 工具类，提供公共使用方法
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/1/8
**/

class JYunTools
{
public:
	JYunTools();
	virtual ~JYunTools();

	//json数组转换为Map
	static QMap<QString, QString> jsonToMap(const QByteArray &bytearray);
	//Map转换为json数组
	static QByteArray mapToJson(const QMap<QString, QString> &map);
	//计算文件MD5
	static QByteArray fileMD5(QString filePath);
	//计算字符串MD5
	static QByteArray stringMD5(QString string);
	//字节码保存为本地图片
	static void byteToLocalImage(const QString &filePath, const QByteArray &byte);
	//内存字符串查着
	static void *memstr(const void *src, quint64 src_len, const void *des);
};

