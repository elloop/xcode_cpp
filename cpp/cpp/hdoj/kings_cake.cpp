#include <iostream>

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

void test()
{
    
    int t ;
    cin >> t;
    
    int m,n;
    while (t--)
    {
        cin >> m >> n;
        cout << cut(m, n) << endl;
    }
}
