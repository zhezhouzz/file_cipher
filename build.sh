#!/bin/bash

clang++ -std=c++11 file_cipher.cpp check.cpp -o check.cpp.out
clang++ -std=c++11 file_cipher.cpp cipher.cpp -o cipher.cpp.out
