#include <iostream>
#include <stack>
#include <limits.h>

class MinStack {
    std::stack<int> stk1_;
    std::stack<int> stk2_;
public:
    MinStack() {
        stk2_.push(INT_MAX);
    }

    void push(int val) {
        stk1_.push(val);
        stk2_.push(std::min(val,stk2_.top()));
    }
    
    void pop() {
        stk1_.pop();
        stk2_.pop();
    }

    int getmin() {
        return stk2_.top();
    }

    int top() {
        return stk1_.top();
    }

};

int main() {
    return 0;
}