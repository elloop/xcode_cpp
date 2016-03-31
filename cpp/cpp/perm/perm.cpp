#include "inc.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

NS_BEGIN(elloop);
NS_BEGIN(perm);

using namespace std;

// recursive perm.
void perm_string(string& s, size_t begin, size_t end)
{
    if (begin == end) 
    {
        psln(s);
    }
    else
    {
        for (size_t i=begin; i<=end; ++i) 
        {
            swap(s[i], s[begin]);
            perm_string(s, begin + 1, end);
            swap(s[i], s[begin]);
        }
    }
}

string insertToString(string str, size_t pos,  char c)
{
   string temp(str.substr(0, pos));
   temp.append(1, c);
   temp.append(str.substr(pos, -1));
   return temp;
}

void new_perm()
{
    string src("abcdefghij");
    vector<string> v {"a"};

    for (int i=1; i<src.size(); ++i) 
    {
        // printContainer(v, "v: ");
        vector<string> temp;
        temp.swap(v);

        // how many string in the vector
        for ( auto & str: temp ) 
        {
            // how long a string is.
            size_t length = str.size();
            for (size_t j=0; j<length+1; ++j)
            {
                v.push_back(insertToString(str, j, src[i]));
            }
        }
    }

    // printContainer(v, "v:");
    psln(v.size());
    for (auto & str : v) 
    {
        psln(str);
    }
}

BEGIN_TEST(Perm, t, @@);


//clock_t begin = clock();
//clock_t end;


//string src("abcdefghij");
//perm_string(src, 0, src.size() - 1);
//end = clock();

//double sec = (end - begin)  CLOCKS_PER_SEC;
//psln(sec);

END_TEST;

NS_END(elloop);
NS_END(perm);
