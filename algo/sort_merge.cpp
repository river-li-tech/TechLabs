#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

//#define MERGE_SORT

namespace merge_sort
{
    ////////////////////////////////////////////////////////
    // ∫œ≤¢≈≈–Ú
    void Merge(std::vector<int>& arr, int p, int q, int r)
    {
        int leftN = q - p + 1;
        int rightN = r - q;

        std::vector<int> L(leftN);
        std::vector<int> R(rightN);

        for (size_t i = 0; i < leftN; i++) {
            L[i] = arr[p + i];
        }
        //L[leftN] = -1;

        for (size_t i = 0; i < rightN; i++) {
            R[i] = arr[q + i + 1];
        }
        //R[rightN] = -1;

        int left = 0, right = 0;
        for (int k = p; k <= r; k++) {
            if (left < leftN && right < rightN) {
                if (L[left] <= R[right]) {
                    arr[k] = L[left];
                    left++;
                } else {
                    arr[k] = R[right];
                    right++;
                }
            } else if (left < leftN) {
                arr[k] = L[left];
                left++;
            } else {
                arr[k] = R[right];
                right++;
            }
        }
    }

    void MergeSort(std::vector<int>& arr, int p, int r)
    {
        if (p < r) {
            int q = (p + r) / 2;
            MergeSort(arr, p, q);
            MergeSort(arr, q + 1, r);
            Merge(arr, p, q, r);
        }
    }
}

#ifdef MERGE_SORT
/////////////////////////////////////////////////////////////////
// ≤‚ ‘¥˙¬Î
using namespace merge_sort;
int main(int argc, char **argv)
{
    std::vector<int> arr = { 2, 8, 7, 1, 3, 5, 6, 4 };
    printf("arr:\n");
    for (std::vector<int>::iterator iter = std::begin(arr); iter != std::end(arr); iter++) {
        printf("%d ", *iter);
    }
    printf("\n");

    MergeSort(arr, 0, arr.size() - 1);

    printf("sorted arr:\n");
    for (std::vector<int>::iterator iter = std::begin(arr); iter != std::end(arr); iter++) {
        printf("%d ", *iter);
    }
    printf("\n");

    getchar();
    return 0;
}
#endif //EXCEPTION