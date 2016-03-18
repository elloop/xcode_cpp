#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(hdoj);

using namespace std;

int cut(int m, int n)
{
    if (m == n)
    {
        return 1;
    }
    else if (m < n)
    {
        return cut(m, n-m) + 1;
    }
    else
    {
        return cut(m-n, n) + 1;
    }
}

BEGIN_TEST(hdoj, kingscake, @@);
int t;
cin >> t;

int m,n;
while (t--)
{
    cin >> m >> n;
    cout << cut(m, n) << endl;
}
END_TEST;
    

NS_END(hdoj);
NS_END(elloop);