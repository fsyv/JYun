#ifndef JYUNSERVER_H_
#define JYUNSERVER_H_
/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 服务类，启动JYun服务
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/3/17
**/

#define SERVER_PORT 65530

#define MAX_LISTEN 102400

struct event_base;
struct bufferevent;

class ThreadPool;
class JYunClient;


class JYunServer{
public:
    explicit JYunServer();
    virtual ~JYunServer();

    void libeventInit();
    void socketInit();
    void init();

    void start();

    void libeventQuit();
    void quit();

    /**
     * @brief: 客户端接受函数
     **/
    static void accpet_cb(evutil_socket_t listener, short event, void *arg);
    static void read_cb(bufferevent *bev, void *arg);
    static void write_cb(bufferevent *bev, void *arg);
    static void error_cb(bufferevent *bev, short event, void *arg);

protected:
    void newConnect(evutil_socket_t sockfd);
private:
    // 线程池
    ThreadPool *m_pThreadPool;
    std::vector<JYunClient *> *m_pClientLists;

    //libevent_base
    event_base *m_pBase;
};

#endif //JYUNSERVER_H_ 