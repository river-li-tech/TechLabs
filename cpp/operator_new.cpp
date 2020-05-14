#pragma warning( disable : 4290 )

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <ctime>
#include <stack>
#include <queue>
#include <memory>

//#define operator_new_class
//#define operator_new_standard
//#define operator_new_signature

// 测试代码
class TestBaseClass
{
private:
    int num;
    char name[32];

public:
    TestBaseClass() : num(0)
    {
        memset(name, 0, 32);
        printf("TestBaseClass constructor TestBaseClass\n");
    }
    ~TestBaseClass()
    {
        printf("TestBaseClass destructor TestBaseClass\n");
    }

#ifdef operator_new_class
    void* operator new(std::size_t sz) throw(std::bad_alloc)
    {
        printf("TestBaseClass class operator new alloc %d bytes\n", sz);
        void* ptr = malloc(sz);
        if (ptr) {
            return ptr;
        } else {
            throw std::bad_alloc();
        }
    }

    void operator delete(void* ptr)
    {
        printf("TestBaseClass class operator delete %p\n", ptr);
        if (ptr) {
            free(ptr);
            ptr = nullptr;
        }
    }
#endif
};

class TestDerivedClass
{
private:
    int age;
    char addr[32];

public:
    TestDerivedClass() : age(0)
    {
        memset(addr, 0, 32);
        printf("TestDerivedClass constructor TestDerivedClass\n");
    }
    ~TestDerivedClass()
    {
        printf("TestDerivedClass destructor TestDerivedClass\n");
    }

#ifdef operator_new_class
    void* operator new(std::size_t sz) throw(std::bad_alloc)
    {
        printf("TestDerivedClass class operator new alloc %d bytes\n", sz);
        void* ptr = malloc(sz);
        if (ptr) {
            return ptr;
        } else {
            throw std::bad_alloc();
        }
    }

    void operator delete(void* ptr)
    {
        printf("TestDerivedClass class operator delete %p\n", ptr);
        if (ptr) {
            free(ptr);
            ptr = nullptr;
        }
    }
#endif
};

/////////////////////////////////////////////////////////////////
// 标准的operator new/delete
#ifdef operator_new_standard
void* operator new(std::size_t sz) throw(std::bad_alloc)
{
    printf("standard operator new alloc %d bytes\n", sz);
    if (sz == 0) {
        sz = 1;
    }

    while (true) {
        void* ptr = malloc(sz);
        if (ptr) {
            return ptr;
        }
        std::new_handler handler = std::get_new_handler();
        if (handler != nullptr) {
            handler();
        } else {
            throw std::bad_alloc();
        }
    }
}

void operator delete(void* ptr) throw()
{
    printf("standard operator delete %p\n", ptr);
    if (ptr) {
        free(ptr);
        ptr = nullptr;
    }
}


void unittest()
{
    printf("-------------------------------\n");
    printf("standard operator new/delete\n");
    //using namespace operator_new_standard;
    TestBaseClass *ptr = new TestBaseClass();
    delete ptr;

    TestDerivedClass *ptr2 = new TestDerivedClass();
    delete ptr2;
}
#endif //operator_new_standard

/////////////////////////////////////////////////////////////////
// 带越界检查的 operator new/delete
#ifdef operator_new_signature
static const int signature = 0xDEADBEEF;    // 边界符
typedef char Byte;
void* operator new(std::size_t sz) throw(std::bad_alloc)
{
    printf("signature operator new alloc %d bytes\n", sz);

    if (sz == 0) {
        sz = 0;
    }

    sz = sz + 2 * sizeof(int);
    void *ptr = malloc(sz);
    if (ptr) {
        // 添加越界检查
        *(static_cast<int*>(ptr)) = signature;
        *(reinterpret_cast<int*>(static_cast<Byte*>(ptr)+sz - sizeof(int))) = signature;
        // 返回真正的地址
        return static_cast<Byte*>(ptr)+sizeof(int);
    }

    while (true) {
        std::new_handler handler = std::get_new_handler();
        if (handler) {
            handler();
        } else {
            throw std::bad_alloc();
        }
    }
}

void operator delete(void* ptr)
{
    printf("signature operator delete %p\n", ptr);

    if (ptr)  {
        ptr = static_cast<Byte*>(ptr) - sizeof(int);
        free(ptr);
    }
}

void* operator new[](std::size_t sz) throw(std::bad_alloc)
{
    printf("signature operator new[] alloc %d bytes\n", sz);
    sz = sz + 2 * sizeof(int);
    void *ptr = malloc(sz);
    if (ptr) {
        // 添加越界检查
        *(static_cast<int*>(ptr)) = signature;
        *(reinterpret_cast<int*>(static_cast<Byte*>(ptr)+sz - sizeof(int))) = signature;
        // 返回真正的地址
        return static_cast<Byte*>(ptr)+sizeof(int);
    } else  {
        throw std::bad_alloc();
    }
}

void operator delete[](void *ptr)
{
    printf("signature operator delete[] %p\n", ptr);
    if (ptr) {
        ptr = static_cast<Byte*>(ptr)-sizeof(int);
        free(ptr);
    }
}

// 测试代码
void unittest()
{
    printf("-------------------------------\n");
    printf("signature operator new/delete\n");
    int *ptr = new int[2];
    //memset(ptr, 0, 2 * sizeof(int));
    ptr[0] = 10;
    ptr[1] = 10;

    delete[] ptr;
}
#endif //operator_new_signature

/////////////////////////////////////////////////////////////////
// 测试代码
//#define OPERATOR_NEW
#ifdef OPERATOR_NEW
int main(int argc, char **argv)
{
    unittest();

    getchar();
    return 0;
}
#endif //OPERATOR_NEW
