#include "inc.h"
#include <algorithm>
#include <bitset>

NS_BEGIN(elloop);
NS_BEGIN(string_algorithm);



bool string_contain_stupid(const std::string &sa, const std::string &sb)
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

bool string_contain_binary_search(std::string &sa, const std::string &sb)
{
    // O(nlogn)
    std::sort(sa.begin(), sa.end());

    // O(n) * O(logn)
    for (size_t i=0; i<sb.size(); ++i ) 
    {
        if (-1 == binary_search_in_string(sa, sb[i])) 
        {
            return false;
        }
    }
    return true;
}

bool string_contain_hash(const std::string &sa, const std::string &sb)
{
    // space O(k) k = non-repeat char set. for example, ASCII 0~127 is enough for visible chars.
    int hash_table[128];
    memset(hash_table, 0, 128 * sizeof(int));

    // O(n) create hash table for sa.
    for (size_t i=0; i<sa.size(); ++i) 
    {
        hash_table[sa[i]] = 1;
    }

    // O(m), find sb[i] in hash table.
    for (size_t i=0; i<sb.size(); ++i) 
    {
        if (0 == hash_table[sb[i]])
        {
            return false;
        }
    }
    return true;
}

bool string_contain_bit_flag(const std::string &sa, const std::string &sb)
{
    // bitset O(1) space
    std::bitset<128> flags;         // 000...0

    // O(n) time
    for (size_t i=0; i<sa.size(); ++i) 
    {
        flags.set(sa[i], 1);
    }

    // O(m) time
    for (size_t i=0; i<sb.size(); ++i) 
    {
        if (!flags.test(sb[i]))
        {
            return false;
        }
    }

    return true;
    
    
    
    
    
    // space O(1), integer bit flag as hash.
    
    /*
     // int128_t flag(0);    // if 128 bit integer is supported.
     // int32_t flag(0);
     
     
     // O(n)
     for (size_t i=0; i<sa.size(); ++i)
     {
     flag |= ( 1 << sa[i]);
     }
     
     // O(m)
     for (size_t i=0; i<sb.size(); ++i)
     {
     if (! (flag & (1 << sb[i])) )
     {
     return false;
     }
     }
     */

}

void run()
{
    std::string sa("abcdsdfadfasvdfefgz");
    std::string sb("efgafadfvcbz");
    
    std::cout << std::boolalpha;
    // psln(string_contain_stupid(sa, sb));
    // psln(string_contain_binary_search(sa, sb));
    // psln(string_contain_hash(sa, sb));
    psln(string_contain_bit_flag(sa, sb));
}

BEGIN_TEST(string_algo, StringContain, @@);

run();

END_TEST;

NS_END(string_algorithm);
NS_END(elloop);

