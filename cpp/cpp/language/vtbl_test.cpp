#include "inc.h"

using namespace std;

NS_BEGIN(elloop);
NS_BEGIN(vtbl);

class A {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    void func1();
    void func2();
private:
    int m_data1, m_data2;
};

class B 
{
};

RUN_GTEST(VtblTest, basic, @@);

psln(sizeof(A));
psln(sizeof(B));


END_TEST;

NS_END(elloop);
NS_END(vtbl);
