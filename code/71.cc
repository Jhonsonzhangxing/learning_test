#include <iostream>
#include <stack>
#include <sstream>

std::string simplify(std::string& str) {
    std::istringstream ss(str);
    std::string tmp;
    std::stack<std::string> stk;
    while(getline(ss,tmp,'/')) {
        if (tmp == "" || tmp == ".") {
            continue;
        } else if (tmp == "..") {
            if (!stk.empty()) {
                stk.pop();
            }
        } else {
            stk.push(tmp);
        }
    }

    if (stk.empty()) return "/";
    tmp.clear();
    while(!stk.empty()) {
         tmp += "/" + stk.top();
         stk.pop();
    }
}