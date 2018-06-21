#ifndef JYUNSERVER_GLOBALPARAMETER_H
#define JYUNSERVER_GLOBALPARAMETER_H

/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 保存全局变量
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/4/6
**/

class FileProcessManager;

class GlobalParameter
{
public:
	static GlobalParameter *getInstance();
	static void destroyInstance();

	bool initFileProcessManager();
	bool init();

    FileProcessManager *getProcessManager() const;
private:
	GlobalParameter();
	~GlobalParameter();

    FileProcessManager *m_pProcessManager;

	static GlobalParameter *m_pInstancer;
	static std::mutex m_mutex;
};

#endif //JYUNSERVER_GLOBALPARAMETER_H
