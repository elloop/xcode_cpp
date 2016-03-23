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


class Base {
public:
    virtual void f() { cout << "Base::f" << endl; }
    virtual void g() { cout << "Base::g" << endl; }
    virtual void h() { cout << "Base::h" << endl; }

};

BEGIN_TEST(VtblTest, basic, @@);

typedef void(*Fun)(void);


Base b;

Fun pFun = NULL, pFun1=NULL, pFun2 = NULL, pFun3 = NULL;
int** pVtab = (int**)&b;
int* v1 = (int*)pVtab[0][0];
int *v2 = (int*)pVtab[0][1];
int *v3 = (int*)pVtab[0][2];

cout <<  v1 << endl;
cout <<  v2 << endl;
cout <<  v3 << endl;

pFun1 = (Fun)v1;
pFun1();
pFun2 = (Fun)v2;
pFun2();
pFun3 = (Fun)v3;
pFun3();


psln(sizeof(A));
psln(sizeof(B));


END_TEST;

NS_END(elloop);
NS_END(vtbl);
