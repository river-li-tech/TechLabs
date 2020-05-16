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

//#define EXCEPTION

namespace exception
{
    class TestExceptionBase
    {
    public:
        int cnt;
        TestExceptionBase(int c) : cnt(c) {}
    };

    class TestExceptionDerived : public TestExceptionBase
    {
    public:
        TestExceptionDerived(int c) : TestExceptionBase(c) {}
    };


    /////////////////////////////////////////////////////////////////
    // 类中异常
    class TestClass
    {
    private:
        int* iptr;
    public:
        //异常保护，确保资源能正确释放
        TestClass() try : iptr(nullptr)
        {
                iptr = new int(10);
                printf("TestClass::Constructor throw exception.\n");
                throw TestExceptionDerived(0);
        } catch (TestExceptionBase& e) {
            e.cnt++;//异常对象用引用捕获，可在捕获后修改
            if (iptr) {
                delete iptr;
                iptr = nullptr;
            }
            printf("TestClass::Constructor hit on Exception Base.\n");
            throw;// 重新抛出，否则还是会返回指针
        } catch (...) {
            printf("TestClass::Constructor hit ...\n");
            throw;// 重新抛出，否则还是会返回指针
        }

        ~TestClass()
        {
            printf("TestClass::Destructor hit.\n");
            if (iptr) {
                delete iptr;
                iptr = nullptr;
            }
        }
    };
}

#ifdef EXCEPTION
/////////////////////////////////////////////////////////////////
// 测试代码
int main(int argc, char **argv)
{
    using namespace exception;
    TestClass* ptr = nullptr;
    try {
        ptr = new TestClass();
    } catch (exception::TestExceptionDerived& e) {
        e.cnt++;
        printf("TestClass catch exception:%d.\n", e.cnt);
    }
    printf("ptr=%p\n", ptr);

    getchar();
    return 0;
}
#endif //EXCEPTION