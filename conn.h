#ifndef CONN_H
#define CONN_H

#include <arpa/inet.h>
#include "fdwrapper.h"


//维护目标服务器，中间服务器，客户端之间的连接，m_cltfd为客户端fd，m_srvfd为目标服务器fd
class conn
{
public:
    conn();
    ~conn();
    void init_clt( int sockfd, const sockaddr_in& client_addr );
    void init_srv( int sockfd, const sockaddr_in& server_addr );
    void reset();
    RET_CODE read_clt();
    RET_CODE write_clt();
    RET_CODE read_srv();
    RET_CODE write_srv();

public:
    static const int BUF_SIZE = 2048;

    char* m_clt_buf;//客户缓冲区
    int m_clt_read_idx;//读指针
    int m_clt_write_idx;//写指针
    sockaddr_in m_clt_address;//客户机地址
    int m_cltfd;//客户socket

    char* m_srv_buf;//服务端缓冲区
    int m_srv_read_idx;//读指针
    int m_srv_write_idx;//写指针
    sockaddr_in m_srv_address;//服务端地址
    int m_srvfd;//服务端socket

    bool m_srv_closed;//此连接是否关闭
};

#endif
