_Pragma("once")

#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(network);

class SimpleSocketServer
{
public:
    SimpleSocketServer();
    ~SimpleSocketServer();
    void start(int argc, char **argv);
};

NS_END(network);
NS_END(elloop);