#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<resources.hpp>

using namespace std;
using namespace rapidxml;

std::string 
readf(const char *path)
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

int 
get_uid(xml_document<> *doc)
{
    int uid;
    xml_attribute<> *attr =  doc->first_node()->first_attribute("OwnerUserId");
    if(attr == 0)
        uid = -1;
    else 
        uid = atoi(attr->value());
    return uid;
}

vector<string>
s_tags(char *s)
{
    vector<string> tags;
    string tag;

    for (; *s!='\0';s++) {
        if(*s == '<')
            tag.clear();
        else if(*s == '>') 
            tags.push_back(tag);
        else
            tag.push_back(*s);
    }
    return tags;
}




