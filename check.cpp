#include "file_cipher.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if(check(argv[1]) != 0) {
        std::cout << "[ERROR] modifyed!" << std::endl;
    }
    return 0;
}