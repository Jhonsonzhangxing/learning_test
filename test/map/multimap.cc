#include <iostream>
#include <map>

int main() {
    std::multimap<int, char> dic;
    dic.emplace(1,'A');
    dic.emplace(2,'B');
    dic.emplace(3,'C');
    dic.emplace(4,'D');
    dic.emplace(4,"C");

    auto range = dic.equal_range(4);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << " => " << it->second << std::endl;
    }

    return 0;
}
