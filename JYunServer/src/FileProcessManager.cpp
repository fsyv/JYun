#include "stdafx.h"
#include "FileProcessManager.h"

#include "TransferProcess.h"

using namespace std;

FileProcessManager::FileProcessManager(uint16_t begin, uint16_t end) :
    m_usBegin(begin),
    m_usEnd(end)
{

}

FileProcessManager::~FileProcessManager()
{
    quit();
}

void FileProcessManager::libeventInit()
{
    m_pBase = event_base_new();
}

void FileProcessManager::socketInit()
{
    evutil_socket_t listener = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_listen_socket_reuseable(listener);

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(m_usEnd);

    if (bind(listener, (sockaddr *)&sin, sizeof(sockaddr)) < 0)
    {
        fprintf(stderr, "FileProcessManager : bind failed by %s\n", strerror(errno));
        exit(1);
    }

    if (listen(listener, MAX_LISTEN) < 0)
    {
        fprintf(stderr, "FileProcessManager : listen failed by %s\n", strerror(errno));
        exit(1);
    }

    evutil_make_socket_nonblocking(listener);

    event *listen_event = event_new(m_pBase, listener, EV_READ | EV_PERSIST, FileProcessManager::accpet_cb, (void *)this);
    event_add(listen_event, nullptr);
}

void FileProcessManager::init()
{
    libeventInit();
    socketInit();

}

void FileProcessManager::start()
{
    event_base_dispatch(m_pBase);
}

void FileProcessManager::libeventQuit()
{
    event_base_free(m_pBase);
    m_pBase = nullptr;
}

void FileProcessManager::quit()
{
    libeventQuit();
}

uint16_t FileProcessManager::addFileProcess(string username, string filename)
{
    unique_lock<mutex> lock(m_mutex);

    //if (m_NamePortMap.size() < m_usEnd - m_usBegin + 1)
        return getIdlePort(username + ":" + filename);
    //else
        //return 0;
}

void FileProcessManager::accpet_cb(evutil_socket_t listener, short event, void *arg)
{
    FileProcessManager *manager = (FileProcessManager *)arg;

    evutil_socket_t fd = accept(listener, nullptr, nullptr);

    if (fd < 0)
    {
        fprintf(stderr, "FileProcessManager : accept failed by %s\n", strerror(errno));
        return;
    }

    fprintf(stderr, "New transfer client\n");

    manager->newConnect(fd);
}

void FileProcessManager::read_cb(bufferevent *bev, void *arg)
{
    TransferProcess *transfer = (TransferProcess *)arg;
    transfer->readMsgBuffer();
}

void FileProcessManager::write_cb(bufferevent *bev, void *arg)
{

}

void FileProcessManager::error_cb(bufferevent *bev, short event, void *arg)
{
    TransferProcess *transfer = (TransferProcess *)arg;
    if (event & BEV_EVENT_TIMEOUT)
        printf("Timed out\n");
    else if (event & BEV_EVENT_EOF)
        delete transfer;
    else if (event & BEV_EVENT_ERROR)
        printf("some other error\n");
}

uint16_t FileProcessManager::getIdlePort(const string name)
{
    uint16_t port = 0;
//    for (uint16_t i = m_usBegin; i <= m_usEnd; ++i)
//    {
//        if(m_NamePortMap.find(i) == m_NamePortMap.end())
//        {
//            port = i;
//            m_NamePortMap[port] = name;
//            break;
//        }
//    }

    port = m_usEnd;

    return port;
}

void FileProcessManager::newConnect(evutil_socket_t sockfd)
{
    evutil_make_socket_nonblocking(sockfd);
    struct bufferevent *bev = bufferevent_socket_new(m_pBase, sockfd, BEV_OPT_CLOSE_ON_FREE);

    //保存客户端信息
    TransferProcess *transfer = new TransferProcess(bev);

    bufferevent_setcb(bev, read_cb, write_cb, error_cb, (void *)transfer);
    bufferevent_enable(bev, EV_READ | EV_WRITE | EV_PERSIST);

    transfer->init();
}
