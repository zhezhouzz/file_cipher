#include "file_cipher.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

constexpr int CIPHER_HEADER_LENGTH = 32;
constexpr int TIME_DEVIATION = 1;

std::string encode(const std::string& str) { return str; }

std::string decode(const std::string& str) { return str; }

int cipher(const char* file_name) {
    std::ofstream output_file(file_name, std::ios::out);
    int error_code = 0;
    struct stat file_stat;
    error_code = stat(file_name, &file_stat);
    if (error_code != 0) {
        return 1;
    }
    std::string content;
    std::stringstream ss;
    ss << file_stat.st_ctime;
    ss >> content;
    content.resize(CIPHER_HEADER_LENGTH);
    output_file.write(encode(content).data(), content.size());
    output_file.close();
    return 0;
}

int check(const char* file_name) {
    int error_code = 0;
    struct stat file_stat;
    error_code = stat(file_name, &file_stat);
    if (error_code != 0) {
        return 1;
    }
    std::ifstream input_file(file_name, std::ios::in);
    input_file.seekg(0, std::ifstream::end);
    size_t count = input_file.tellg();
    if (int(count) < CIPHER_HEADER_LENGTH) {
        return 2;
    }
    input_file.seekg(0, std::ifstream::beg);
    char charv[CIPHER_HEADER_LENGTH];
    input_file.read(charv, CIPHER_HEADER_LENGTH);
    input_file.close();
    std::string content(charv);
    content = decode(content);
    std::stringstream ss;
    ss << content;
    time_t embedded_ctime;
    ss >> embedded_ctime;
    std::cout << "check embedded_ctime = " << embedded_ctime << std::endl;
    std::cout << "check file_stat.st_ctime = " << file_stat.st_ctime << std::endl;
    std::cout << "check file_stat.st_atime = " << file_stat.st_atime << std::endl;
    std::cout << "check file_stat.st_mtime = " << file_stat.st_mtime << std::endl;
    if (((embedded_ctime - file_stat.st_ctime) > TIME_DEVIATION) ||
        ((file_stat.st_ctime - embedded_ctime) > TIME_DEVIATION)) {
        return 3;
    }
    return 0;
}