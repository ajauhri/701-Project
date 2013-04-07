#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<resources.hpp>

using namespace std;

std::string readf(const char *path)
{
    string buffer;
    ifstream file (path);
    if (!file) {
        throw "Could not open file";
    }

    /* to avoid several allocations and copies of data */
    file.seekg(0, ios::end);
    buffer.reserve(file.tellg());
    file.seekg(0, ios::beg);

    buffer.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    return buffer;
}


