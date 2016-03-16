#include "network/simple_socket_app.h"

#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


NS_BEGIN(elloop);
NS_BEGIN(network);

#define MAXLINE 4096

SimpleSocketServer::SimpleSocketServer()
{
    
}

SimpleSocketServer::~SimpleSocketServer()
{
    
}

void SimpleSocketServer::start(int argc, char **argv)
{
    int     listenfd;
    int     connfd;
    struct  sockaddr_in server_address;
    char    buff[4096];
    size_t  n;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("create socket error: %s, errno: %d\n", strerror(errno), errno);
        exit(0);
    }
    
    memset(&server_address, 0, sizeof(server_address));
    
    server_address.sin_family       = AF_INET;
    server_address.sin_addr.s_addr  = htonl(INADDR_ANY);
    server_address.sin_port         = htons(6666);
    
    if (bind(listenfd, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
    {
        printf("bind socket error: %s, errno: %d\n", strerror(errno), errno);
        exit(0);
    }
    
    pcln("waiting for client's request");
    while (1)
    {
        if (-1 == (connfd = accept(listenfd, (struct sockaddr*)nullptr, nullptr)))
        {
            printf("accept socket error: %s, errno: %d\n", strerror(errno), errno);
            continue;
        }
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = 0;
        printf("recv msg from client: %s\n", buff);
        close(connfd);
    }
    
    close(listenfd);
}

NS_END(network);
NS_END(elloop);





