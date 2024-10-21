#include <iostream>

bool isvalid(std::string& str) {
    std::string stk("");
    for (auto itr : str) {
        if (itr == '(' || itr == '[' ||itr == '{') {
            stk.append(std::to_string(itr));
        } else if((itr == ')' || itr == ']' || itr == '}') && itr != stk.back()) {
            return false;
        } else {
            stk.pop_back();
        }
    }
    return stk.empty();
}