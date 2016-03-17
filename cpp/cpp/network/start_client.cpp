#include "simple_socket_client.h"

int main(int argc, char** argv) 
{
    elloop::network::SimpleSocketClient client;
    client.start(argc, argv);
    return 0;
}
