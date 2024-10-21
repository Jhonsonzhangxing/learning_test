#include<iostream>
#include<vector>

int findMor(std::vector<int>& vec) {
    int k = 0, cnt = 0;

    for (auto itr : vec) {
        if (k == 0) {
            k = itr;
            cnt++;
        } else {
            cnt += (k == itr) ? 1 : -1; 
        }
    }
    return ;
}


int main() {

    return 0;
}