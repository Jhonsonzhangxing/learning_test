#include<iostream>
#include <vector>
#include <unordered_set>

bool minflipnum(std::vector<std::vector<int>>& vec) {
    std::unordered_set<std::string> set;
    for (auto& itr : vec) {
        std::string s;
        for (auto it : itr) {
            s.append(std::string(itr[0] == 0 ? std::to_string(it) : std::to_string(it^1)));
        }
        set.emplace(s);
    }
    return set.size() == 1;

}

int main() {
    std::vector<std::vector<int>> vec = {{0,1,0},{1,0,1},{0,1,0}}; //[[0,1,0],[1,0,1],[0,1,0]];
    std::cout << minflipnum(vec) << std::endl;
    return 0;
}