#include <iostream>
#include <vector>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int mem_size = *argv[0];
    std::cout << "argc: " << argc << ", first_arg: " << argv[0] << ", 2: " << argv[1] << std::endl;
    std::vector<char*> arr_char;
    int cin;
    sleep(10);
    for (int j = 0; j < 2064; ++j) {
        char* buffer = new char[mem_size];
        for (int i = 0; i < mem_size; ++i) {
            buffer[i] = 'a';
        }
        arr_char.emplace_back(buffer);
    }

    
    std::cin >> cin;
    std::cout << "cin: " << cin << std::endl;

    for ( int j = 0; j < 2065; j++) {
        delete[] arr_char[j];
    }   

    while(1) sleep(10);

    return 0;
}

//ps -o majflt,minflt -C program
// https://blog.51cto.com/u_16099258/9377782