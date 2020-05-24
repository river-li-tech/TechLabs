#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <vector>
#include <ctime>
#include <stack>
#include <queue>
#include <memory>

#define INSERT_SORT

namespace INSERT_SORT_NS
{
    ////////////////////////////////////////////////////////
    // 插入排序
    void InsertSort(std::vector<int>& arr)
    {
        using std::swap;
        int len = arr.size();
        if (len <= 1) {
            return;
        }

        int i = 0;
        int key = 0;
        for (int j = 1; j < len; j++) {
            key = arr[j];
            i = j - 1;

            while (i >= 0 && arr[i] > key) {    // 移动中间的数据
                arr[i + 1] = arr[i];
                i--;
            }
            arr[i + 1] = key;
        }
    }

    // 插入排序-改进插入查找为二分查找，时间复杂度变为NlgN
    void InsertSort(std::vector<int>& arr)
    {
        using std::swap;
        int len = arr.size();
        if (len <= 1) {
            return;
        }

        int i = 0;
        int key = 0;
        for (int j = 1; j < len; j++) {
            key = arr[j];
            i = j - 1;

            //使用二分查找
            int min = 0;
            int max = j - 1;
            for (int i = 0; i < std::log2(j); i++) {
                if (arr[i] == key) {

                }


            }
            while (i >= 0 && arr[i] > key) {    // 移动中间的数据
                arr[i + 1] = arr[i];
                i--;
            }
            arr[i + 1] = key;
        }
    }
}

#ifdef INSERT_SORT
/////////////////////////////////////////////////////////////////
// 测试代码
using namespace INSERT_SORT_NS;
int main(int argc, char **argv)
{
    std::vector<int> arr = { 2, 8, 7, 1, 3, 5, 6, 4 };
    printf("arr:\n");
    for (std::vector<int>::iterator iter = std::begin(arr); iter != std::end(arr); iter++) {
        printf("%d ", *iter);
    }
    printf("\n");

    InsertSort(arr);

    printf("sorted arr:\n");
    for (std::vector<int>::iterator iter = std::begin(arr); iter != std::end(arr); iter++) {
        printf("%d ", *iter);
    }
    printf("\n");

    getchar();
    return 0;
}
#endif //EXCEPTION