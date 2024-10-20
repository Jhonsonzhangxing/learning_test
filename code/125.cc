#include <iostream>


bool isPalindrome(std::string& str) {
    int i = 0, j = str.size() - 1;
    while(i < j) {
        if (!isalnum(str[i])) {
            i++; 
        } else if(!isalnum(str[j])) {
            j--;
        } else if(str[i] == str[j]){
            i++;
            j--;
        } else {
            return false;
        }
    }
    return true;
}

int main() {

}