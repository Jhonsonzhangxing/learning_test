//A(1,2,3) B(3,4,5) 重复的数字是一个
//求任意数字放在两个容器中，重复数字的个数

#include <iostream>
#include <vector>
#include <set>
using namespace std;

std::vector<int> A;
std::vector<int> B;
int repeatNum = 0;

int findRepeatNum(std::vector<int>& A, std::vector<int>& B) {
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < B.size(); ++j) {
            if (A[i] == B[j]) {
                repeatNum++;
                break;
            }
        }
    }

    return repeatNum;
}

int findRepeatNum_set(std::set<int>& A, std::set<int>& B) {
    for (auto itr = A.begin(); itr != A.end(); ++itr) {
        if (B.count(*itr) != 0) {
            repeatNum++;
            continue;
        }
    }

    return repeatNum;
}

int main() {
    bool bFirst = true;

    return 0;
}