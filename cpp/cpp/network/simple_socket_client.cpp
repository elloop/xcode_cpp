#include "network/simple_socket_client.h"

#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


NS_BEGIN(elloop);
NS_BEGIN(network);

#define MAXLINE 4096

SimpleSocketClient::SimpleSocketClient()
{
    
}

SimpleSocketClient::~SimpleSocketClient()
{
    
}

void SimpleSocketClient::start(int argc, char **argv)
{
    /*
    int     socket_fd;
    struct  sockaddr_in server_address;
    char    send_line[4096];

    if (argc < 2) 
    {
        pln("wrong arg");
        exit(0);
    }
    
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("create socket error: %s, errno: %d\n", strerror(errno), errno);
        exit(0);
    }
    
    memset(&server_address, 0, sizeof(server_address));
    
    server_address.sin_family       = AF_INET;
    server_address.sin_port         = htons(6666);
    
    
    if (inet_pton(AF_INET, argv[1], &server_address.sin_addr) <= 0)
    {
        printf("inet_pton error: %s\n", argv[1]);
        exit(0);
    }
    
    if (connect(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        printf("connect error: %s\n", strerror(errno));
        exit(0);
    }
    
    
    pcln("send msg to server");
    
    fgets(send_line, 4096, stdin);
    
    if (send(socket_fd, send_line, strlen(send_line), 0) < 0) {
        printf("send msg error: %s\n", strerror(errno));
        exit(0);
    }
    
    close(socket_fd);
    
    exit(0);
     */
}

NS_END(network);
NS_END(elloop);





