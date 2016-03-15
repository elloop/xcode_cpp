#include "string_algorithm.h"

NS_BEGIN(elloop);
NS_BEGIN(string_algorithm);

StringAlgoSolution::StringAlgoSolution()
{
}

StringAlgoSolution::~StringAlgoSolution()
{
}

void StringAlgoSolution::run()
{
    std::string sa("hello");
    std::string sb("hel");
    psln(string_contain(sa, sb));
}

bool StringAlgoSolution::string_contain(const std::string &sa, const std::string &sb) const
{
    return false;
}


NS_END(string_algorithm);
NS_END(elloop);

