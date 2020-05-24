#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

//#define ADD_BINARY

namespace NS_ADD_BINARY
{
    ///////////////////////////////////////////
    // 二进制数加法
    void AddBinary(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C)
    {
        //检验数组大小
        if (A.size() != B.size() || C.size() != (A.size() + 1)) {
            return;
        }

        int carry = 0;
        int i = A.size() - 1;
        for (; i >= 0; i--) {
            C[i + 1] = (A[i] + B[i] + carry) % 2;
            carry = (A[i] + B[i] + carry) / 2;
        }
        C[0] = carry;
    }
}

#ifdef ADD_BINARY
/////////////////////////////////////////////////////////////////
// 测试代码
using namespace NS_ADD_BINARY;
int main(int argc, char **argv)
{
    std::vector<int> A = { 0, 1, 1, 0 };
    std::vector<int> B = { 1, 0, 1, 1 };
    std::vector<int> C(5, 0);
    AddBinary(A, B, C);

    std::for_each(A.begin(), A.end(), [](int v) { printf("%d ", v); });
    printf("\n");
    std::for_each(B.begin(), B.end(), [](int v) { printf("%d ", v); });
    printf("\n");
    std::for_each(C.begin(), C.end(), [](int v) { printf("%d ", v); });
    printf("\n");

    getchar();
    return 0;
}
#endif //EXCEPTION