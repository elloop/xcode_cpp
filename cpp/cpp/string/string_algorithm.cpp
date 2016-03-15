#include "string_algorithm.h"
#include <algorithm>

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
    
    std::cout << std::boolalpha;
    // psln(string_contain_stupid(sa, sb));
    psln(string_contain_binary_search(sa, sb));
}

bool StringAlgoSolution::string_contain_stupid(const std::string &sa, const std::string &sb) const
{
    for (size_t i=0; i<sb.size(); ++i)
    {
        bool found(false);
        for (size_t j=0; j<sa.size(); ++j)
        {
            if (sb[i] == sa[j])
            {
                found = true;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

int binary_search_in_string(const std::string &s, char c)
{
    size_t low = 0;
    size_t high = s.size() - 1;
    size_t mid = 0;

    while (low <= high) 
    {
        mid = (high + low) / 2;
        if (c < s[mid]) 
        {
            high = mid - 1;
        }
        else if (c > s[mid])
        {
            low = mid + 1;
        }
        else
        {
            return static_cast<int>(mid);
        }
    }
    return -1;
}

bool StringAlgoSolution::string_contain_binary_search(std::string &sa, const std::string &sb) const
{
    // O(nlogn)
    std::sort(sa.begin(), sa.end());

    // O(nlogn)
    for (size_t i=0; i<sb.size(); ++i ) 
    {
        if (-1 == binary_search_in_string(sa, sb[i])) 
        {
            return false;
        }
    }
    return true;
}

NS_END(string_algorithm);
NS_END(elloop);

