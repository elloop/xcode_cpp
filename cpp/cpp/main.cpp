#include <iostream>
#include "string/string_algorithm.h"
#include "network/simple_socket_app.h"
using namespace std;
using namespace elloop;

int main(int argc, char ** argv)
{
    
//    elloop::string_algorithm::StringAlgoSolution s;
//    s.run();
    network::SimpleSocketServer s;
    s.start(argc, argv);
    return 0;
}
