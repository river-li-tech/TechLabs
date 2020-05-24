#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

//#define SEARCH_BINARY

namespace NS_SEARCH_BINARY
{
    ////////////////////////////////////////////////////////
    // 二分查找-递归式
    int BinarySearch(std::vector<int>& arr, int val, int p = -1, int q = -1)
    {
        if (p < 0) {
            p = 0;
        }
        if (q < 0) {
            q = arr.size() - 1;
        }

        if (p <= q) {
            int r = (p + q) / 2;
            if (arr[r] == val) {
                return r;
            } else if (arr[r] < val) {
                return BinarySearch(arr, val, r + 1, q);
            } else {
                return BinarySearch(arr, val, p, r - 1);
            }
        }
        return -1;
    }

    // 二分查找-循环式
    int BinarySearch_Iter(std::vector<int>& arr, int val)
    {
        int min = 0;
        int max = arr.size() - 1;
        int mid = (min + max) / 2;
        for (int i = 0; i < (std::log2(arr.size())); i++) {
            if (arr[mid] == val) {
                return mid;
            } else if (arr[mid] > val) {
                max = mid - 1;
                mid = (min + max) / 2;
            } else {
                min = mid + 1;
                mid = (min + max) / 2;
            }
        }
        return -1;
    }
}

#ifdef SEARCH_BINARY
/////////////////////////////////////////////////////////////////
// 测试代码
using namespace NS_SEARCH_BINARY;
int main(int argc, char **argv)
{
    std::vector<int> arr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int val = 4;
    int idx = BinarySearch(arr, val);
    int idx_iter = BinarySearch_Iter(arr, val);

    std::for_each(arr.begin(), arr.end(), [](const int& v){printf("%d ", v); });
    printf("\n");

    printf("binary search %d at %d\n", val, idx);
    printf("binary search(iterator) %d at %d\n", val, idx_iter);

    getchar();
    return 0;
}
#endif //EXCEPTION