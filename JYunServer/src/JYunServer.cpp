#include "stdafx.h"

#include "JYunServer.h"

#include "ThreadPool.h"
#include "JYunClient.h"

using namespace std;

JYunServer::JYunServer() : m_pThreadPool(nullptr),
                           m_pClientLists(nullptr),
                           m_pBase(nullptr)
{
    init();
}

JYunServer::~JYunServer()
{
    quit();
}

void JYunServer::libeventInit()
{
    m_pBase = event_base_new();
}

void JYunServer::socketInit()
{
    evutil_socket_t listener = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_listen_socket_reuseable(listener);

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(SERVER_PORT);

    if (bind(listener, (sockaddr *)&sin, sizeof(sockaddr)) < 0)
    {
        fprintf(stderr, "JYunServer : bind failed by %s\n", strerror(errno));
        exit(1);
    }

    if (listen(listener, MAX_LISTEN) < 0)
    {
        fprintf(stderr, "JYunServer : listen failed by %s\n", strerror(errno));
        exit(1);
    }

    evutil_make_socket_nonblocking(listener);

    event *listen_event = event_new(m_pBase, listener, EV_READ | EV_PERSIST, JYunServer::accpet_cb, (void *)this);
    event_add(listen_event, nullptr);
}

void JYunServer::init()
{
    //初始化顺序:
    //1 线程资源
    //2 本类基础资源
    //3 网络库

    m_pThreadPool = new ThreadPool;
    m_pClientLists = new vector<JYunClient *>;

    libeventInit();
    socketInit();
}

void JYunServer::start()
{
    event_base_dispatch(m_pBase);
}

void JYunServer::libeventQuit()
{
    event_base_free(m_pBase);
    m_pBase = nullptr;
}

void JYunServer::quit()
{
    libeventQuit();
}

void JYunServer::accpet_cb(evutil_socket_t listener, short event, void *arg)
{
    JYunServer *server = (JYunServer *)arg;

    evutil_socket_t fd = accept(listener, nullptr, nullptr);

    if (fd < 0)
    {
        fprintf(stderr, "JYunServer : accept failed by %s\n", strerror(errno));
        return;
    }

    server->newConnect(fd);
}

void JYunServer::read_cb(bufferevent *bev, void *arg)
{
    JYunClient *client = (JYunClient *)arg;
    client->readMsgBuffer();
}

void JYunServer::write_cb(bufferevent *bev, void *arg)
{
    JYunClient *client = (JYunClient *)arg;
    client->refreshContactTime();
}

void JYunServer::error_cb(bufferevent *bev, short event, void *arg)
{
    JYunClient *client = (JYunClient *)arg;
    if (event & BEV_EVENT_TIMEOUT)
    {
        printf("Timed out\n");
    }
    else if (event & BEV_EVENT_EOF)
        client->close();
    else if (event & BEV_EVENT_ERROR)
    {
        printf("some other error\n");
    }
    bufferevent_free(bev);
}

void JYunServer::newConnect(evutil_socket_t sockfd)
{
    struct bufferevent *bev = bufferevent_socket_new(m_pBase, sockfd, BEV_OPT_CLOSE_ON_FREE);

    //保存客户端信息
    JYunClient *client = new JYunClient(bev);

    bufferevent_setcb(bev, read_cb, write_cb, error_cb, (void *)client);
    bufferevent_enable(bev, EV_READ | EV_WRITE | EV_PERSIST);

    client->init();
    m_pClientLists->push_back(client);
}
