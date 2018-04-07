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
* @brief : 消息缓存
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/4/6
**/

typedef unsigned long long int memsize;

struct Msg;

class JYunStringBuffer
{
public:
	JYunStringBuffer(const memsize &size = 1024);
	~JYunStringBuffer();

	// \0 结尾的串
	void append(const char *szbuf);
	// 非\0 结尾的串
	void append(const char *buf, const size_t &len);
	//保证每次都是头部在首尾
	void alignmentBuffer();
	//调整内存
	void adjustMemory();

	Msg *getMsg();
private:
	char *m_pBuffer;

	//总长度
	memsize m_allSize;
	//当前长度
	memsize m_size;
	//初试长度
	memsize m_initSize;
};

