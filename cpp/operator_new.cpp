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
using namespace std;

/////////////////////////////////////////////////////////////////
void* operator new(std::size_t sz)
{
    printf("new %d\n", sz);
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
        }
        else {
            throw std::bad_alloc();
        }
    }
}

void operator delete(void* ptr)
{
    printf("delete %d\n", ptr);
    if (ptr)
    {
        free(ptr);
        ptr = nullptr;
    }
}

class TestBase
{
public:
    int id;
    TestBase() : id(100)
    {
    }
};

/////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    TestBase * ptr = new TestBase();
    delete ptr;

    getchar();
    return 0;
}