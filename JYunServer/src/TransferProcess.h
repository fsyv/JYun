#ifndef JYUNSERVER_TRANSFERPROCESS_H
#define JYUNSERVER_TRANSFERPROCESS_H
/******************************************************************************
*                 JJJJJJJ   YY    YY                                          *
*                   JJJ      YY  YY                                           *
*                   JJJ       YYYY     u      u    n  nnnn                    *
*                   JJJ        YY      u     uu    n n   nn                   *
*             JJJ  JJJ         YY      uu   u u    nn     n                   *
*               JJJJJ          YY       uuuu  u    n      n                   *
*******************************************************************************
* @brief : 文件传输控制
* @author : fsyv
* @email : fsyv@gmail.com
* @date : 2018/6/12
**/

#include "Msg.h"

//接收Buf最大缓存
#define RECV_BUF_MAX_SIZE 64 * 1024

struct bufferevent;

class TransferProcess {
    using string = std::string;
public:
    explicit TransferProcess(bufferevent *bev);
    virtual ~TransferProcess();

    bool init();
    void close();
    void readMsgBuffer();

protected:
    int upload(string filename, uint64_t offset, int size, char *data);
    int download(string filename, uint64_t offset, int size);

protected:
    int recvFileProcessMsg(FileProcessMsg *fMsg);
    int sendFilePrecessMsg(FileProcessMsg::FileProcessType type, string filename, uint32_t  timestamp = time(nullptr), uint64_t offset = 0ull,
                           int size = 0ull, char *data = nullptr);

private:
    bufferevent *m_pBufferevent;
};


#endif //JYUNSERVER_TRANSFERPROCESS_H
