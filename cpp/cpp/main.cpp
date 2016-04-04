#include <iostream>
#include "network/simple_socket_app.h"
#include "inc.h"
using namespace std;
using namespace elloop;

int main(int argc, char ** argv)
{
//    elloop::string_algorithm::StringAlgoSolution s;
//    s.run();
//    network::SimpleSocketServer s;
//    s.start(argc, argv);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
