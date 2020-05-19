#define _CRTDBG_MAP_ALLOC
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

// ‘ÿ»ÎCRTµ˜ ‘ø‚
#include <crtdbg.h>

#define MEMORY_LEAK

namespace memoryleak
{

}

#ifdef MEMORY_LEAK
/////////////////////////////////////////////////////////////////
// ≤‚ ‘¥˙¬Î
using namespace memoryleak;
void GetMemory(char *p, int num)
{
    p = (char*)malloc(sizeof(char)* num);
}

int main(int argc, char **argv)
{
    _CrtMemState state1, state2;
    _CrtMemCheckpoint(&state1);

    char *str = NULL;
    GetMemory(str, 100);
    std::cout << "Memory leak test!" << std::endl;

    _CrtMemCheckpoint(&state2);

    _CrtMemState state3;
    if (_CrtMemDifference(&state3, &state1, &state2)) {
        _CrtMemDumpStatistics(&state3);
    }
    //_CrtDumpMemoryLeaks();

    getchar();
    return 0;
}
#endif //EXCEPTION