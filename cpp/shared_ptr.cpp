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

//#define SHARED_PTR

namespace sharedptr
{
    class Point
    {
    public:
        Point(int xVal = 0, int yVal = 0) :x(xVal), y(yVal)
        {
            printf("Point() (%d,%d)\n", x, y);
        }
        ~Point()
        {
            printf("~Point() (%d,%d)\n", x, y);
        }

        int getX() const { return x; }
        int getY() const { return y; }
        void setX(int xVal) { x = xVal; }
        void setY(int yVal) { y = yVal; }

    private:
        int x, y;
    };

    /////////////////////////////////////////////////////////////////

    template<typename T>
    class DefaultDeleter
    {
    public:
        void operator()(T* p) { delete p; }
    };

    template<class T, class Deleter = DefaultDeleter<T>>
    class SharedPtr
    {
        // 计数
        typedef struct Aux
        {
            unsigned count;
            Aux() : count(1) {}
            ~Aux() {}
            virtual void Destroy() {}

            unsigned Inc() { return ++count; }
            unsigned Dec() { return --count; }
        }Aux;

        // 删除器
        template<typename T, typename D>
        struct AuxImpl : Aux
        {
        public:
            AuxImpl(T *u, D d) : ptr(u), deleter(d) {}
            void Destroy() { deleter(ptr); }

        private:
            T *ptr;
            D deleter;
        };

    public:
        SharedPtr() : pdata(), pcnt() {}
        SharedPtr(T *ptr) : pdata(ptr), pcnt(new AuxImpl<T, Deleter>(ptr, Deleter())) {}
        SharedPtr(T *ptr, Deleter del) : pdata(ptr), pcnt(new AuxImpl<T, Deleter>(ptr, del)) {}

        ~SharedPtr()
        {
            if (!Dec()) {   
                Destroy();
            }
        }

        // 拷贝构造函数和运算符
        SharedPtr(const SharedPtr& rv) : pdata(rv.pdata), pcnt(rv.pcnt) { Inc(); }
        SharedPtr& operator=(const SharedPtr& rv)
        {
            if (this != &rv) {
                pdata = rv.pdata;
                pcnt = rv.pcnt;
                Inc();
            }
            return *this;
        }

        // 重载载入符
        T* operator->() { return pdata; }
        T& operator*() { return *pdata; }

        // 返回原始指针
        T* GetPtr() const { return pdata; }

    private:
        int Inc() { return pcnt ? pcnt->Inc() : 0; }
        int Dec() { return pcnt ? pcnt->Dec() : 0; }
        void Destroy() { if (pcnt) { pcnt->Destroy(); delete pcnt; } }

    private:
        T *pdata;
        Aux *pcnt;
    };
}

#ifdef SHARED_PTR
/////////////////////////////////////////////////////////////////
// 测试代码
using namespace sharedptr;

SharedPtr<Point> TestSharedPtr(SharedPtr<Point> sptr)
{
    Point *newPoint = new Point(sptr->getX() + 100, sptr->getY() + 200);
    SharedPtr<Point> newPtr(newPoint);
    return newPtr;
}

void PointDeleter(Point* ptr)
{
    printf("PointDeleter\n");
    if (ptr) {
        delete ptr;
    }
}

int main(int argc, char **argv)
{
    {
        Point * point = new Point(10, 20);
        SharedPtr<Point> sptr(point);
        SharedPtr<Point> sptr2(sptr);

        SharedPtr<Point> sptr3 = TestSharedPtr(sptr);
    }

    {
        typedef void (*DeleterFunc)(Point*);
        Point * point = new Point(1000, 2000);
        SharedPtr<Point, DeleterFunc> sptr(point, PointDeleter);
    }

    getchar();
    return 0;
}
#endif //EXCEPTION