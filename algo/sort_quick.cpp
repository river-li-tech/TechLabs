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

//#define QUICK_SORT

namespace quick_sort
{
    ////////////////////////////////////////////////////////
    // 快速排序
    int Partion(std::vector<int>& arr, int p, int r)
    {
        using std::swap;
        int x = arr[r];
        int i = p - 1;
        for (int j = p; j < r; j++) {
            if (arr[j] <= x) {  //arr[j] >= x 降序
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[r]);
        return i + 1;
    }

    void QuickSort(std::vector<int>& arr, int p, int r)
    {
        if (p < r) {
            int q = Partion(arr, p, r);
            QuickSort(arr, p, q - 1);
            QuickSort(arr, q + 1, r);
        }
    }

    ////////////////////////////////////////////////////////
    // 随机化版本
    int PartionRand(std::vector<int>& arr, int p, int r)
    {
        using std::swap;
        int rnd = static_cast<int>(p + (1.0f * std::rand() / RAND_MAX) * (r - p));
        swap(arr[rnd], arr[r]);
        return Partion(arr, p, r);
    }

    void QuickSortRand(std::vector<int>& arr, int p, int r)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        if (p < r) {
            int q = PartionRand(arr, p, r);
            QuickSort(arr, p, q - 1);
            QuickSort(arr, q + 1, r);
        }
    }
}

#ifdef QUICK_SORT
/////////////////////////////////////////////////////////////////
// 测试代码
using namespace quick_sort;
int main(int argc, char **argv)
{
    std::vector<int> arr = {2, 8, 7, 1, 3, 5, 6, 4};
    printf("arr:\n");
    for (std::vector<int>::iterator iter = std::begin(arr); iter != std::end(arr); iter++) {
        printf("%d ", *iter);
    }
    printf("\n");

    //QuickSort(arr, 0, arr.size() - 1);
    QuickSortRand(arr, 0, arr.size() - 1);

    printf("sorted arr:\n");
    for (std::vector<int>::iterator iter = std::begin(arr); iter != std::end(arr); iter++) {
        printf("%d ", *iter);
    }
    printf("\n");

    getchar();
    return 0;
}
#endif //EXCEPTION