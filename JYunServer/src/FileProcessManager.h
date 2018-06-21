#ifndef JYUNSERVER_FILEPROCESSMANAGER_H
#define JYUNSERVER_FILEPROCESSMANAGER_H
/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 文件进程管理器
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/6/12
**/

// 数据传输端口使用范围
#define TRANSFER_PORT_BEGIN     50000
#define TRANSFER_PORT_END       65520

#define MAX_LISTEN 102400

struct event_base;
struct bufferevent;

class FileProcessManager {
    using string = std::string;
public:
    explicit FileProcessManager(const uint16_t begin = TRANSFER_PORT_BEGIN, const uint16_t end = TRANSFER_PORT_END);
    virtual ~FileProcessManager();

    void libeventInit();
    void socketInit();
    void init();
    void start();
    void libeventQuit();
    void quit();
    uint16_t addFileProcess(string username, string filename);
	
    /**
     * @brief: 客户端接受函数
     **/
    static void accpet_cb(evutil_socket_t listener, short event, void *arg);
    static void read_cb(bufferevent *bev, void *arg);
    static void write_cb(bufferevent *bev, void *arg);
    static void error_cb(bufferevent *bev, short event, void *arg);

protected:
    uint16_t getIdlePort(const string name);
    void newConnect(evutil_socket_t sockfd);
private:
    const uint16_t m_usBegin;
    const uint16_t m_usEnd;
    std::mutex m_mutex;
	
    //libevent_base
    event_base *m_pBase;
};


#endif //JYUNSERVER_FILEPROCESSMANAGER_H
