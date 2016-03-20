#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(cpp11_review);


// ============================================================================
//
// old c++98 deep copy consumption demo 
//
// ============================================================================

class HasPtrMem
{
public:
    HasPtrMem() : ptr(new int(0))
    {
        LOGD("constructor: %d\n", ++s_ctr);
    }

    HasPtrMem(const HasPtrMem &h) : ptr(new int(*h.ptr))
    {
        LOGD("copy constructor: %d\n", ++s_cptr);
    }

    ~HasPtrMem()
    {
        if (ptr) 
        {
            delete ptr;
        }
        LOGD("~HasPtrMem(): %d\n", ++s_dtr);
    }

    int *ptr;

    static int s_ctr;
    static int s_cptr;
    static int s_dtr;
};

int HasPtrMem::s_ctr = 0;
int HasPtrMem::s_cptr = 0;
int HasPtrMem::s_dtr = 0;


HasPtrMem getTemp()
{
    return HasPtrMem();
    // ctor 1 : construct temp.
    // cptr 1 : copy construct return value from temp.
    // dtr 1 : release temp value.
}

BEGIN_TEST(Cpp11Review, CopyConsume, @@);

HasPtrMem a = getTemp();
// cptr 2 : from return value to a.
// dtr 2: delete return value.
// dtr 3: delete a.

END_TEST;

// ============================================================================
//
// use move constructor 
//
// ============================================================================

class UseMoveCtr
{
public:
    UseMoveCtr() : ptr(new int(0))
    {
        LOGD("ctr: %d\n", ++s_ctr);
    }

    ~UseMoveCtr()
    {
        if (ptr) {
            delete ptr;
        }
        LOGD("dtr: %d\n", ++s_dtr);
    }

    UseMoveCtr(const UseMoveCtr & other) : ptr(new int(*other.ptr))
    {
        LOGD("cptr: %d\n", ++s_cptr);
    }
    UseMoveCtr(UseMoveCtr && moved) : ptr(moved.ptr)
    {
        moved.ptr = nullptr;
        LOGD("mctr: %d\n", ++s_mctr);
    }

    int *ptr;

    static int s_ctr;
    static int s_cptr;
    static int s_dtr;
    static int s_mctr;

};

int UseMoveCtr::s_ctr = 0;
int UseMoveCtr::s_cptr = 0;
int UseMoveCtr::s_dtr = 0;
int UseMoveCtr::s_mctr = 0;

UseMoveCtr getTempUse()
{
    UseMoveCtr t;

    std::cout << "address in: " << __func__ << " is: " << std::hex << t.ptr << std::endl;

    return t;
    // ctr 1 : construct temp
    // mctr 1 : move construct temp by moving from temp
    // dtr 1 : delete temp
}

BEGIN_TEST(Cpp11Review, UseMoveConstructor, @);

UseMoveCtr a = getTempUse();
std::cout << "address in: " << __func__ << " is " << std::hex << a.ptr << std::endl;
// mctr 2: move contruct a by moving from return value.
// dtr 2 : delete return value.
// dtr 3 : delete a.

END_TEST;

NS_END(cpp11_review);
NS_END(elloop);

