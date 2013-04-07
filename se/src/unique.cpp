#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<vector>
#include<map>
#include<rapidxml/rapidxml_print.hpp>
#include<rapidxml/rapidxml.hpp>
#include<resources.hpp>
#include<boost/iostreams/device/mapped_file.hpp>

using namespace std;
using namespace rapidxml;

ofstream ques_fd("../se-data/questions", fstream::app);
ofstream ans_fd("../se-data/answers", fstream::app);
ofstream uniq_tags("../se-data/tags", fstream::app);

map<std::string, int> tag_counter;

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

void 
proc_question(std::string s)
{
    xml_document<> doc;
    doc.parse<0>(&s[0]);

    int id = atoi(doc.first_node()->first_attribute("Id")->value());
    int uid = get_uid(&doc); 
    int score = atoi(doc.first_node()->first_attribute("Score")->value());
    ques_fd<<id<<','<<uid<<','<<score;
    
    vector<string> tags = s_tags(doc.first_node()->first_attribute("Tags")->value());
    
    if(tags.size() == 0)
        throw "No tags in question";

    for (vector<string>::iterator it=tags.begin(); it!=tags.end(); ++it) {
        ques_fd<<','<<*it;
        if(tag_counter.find(*it) == tag_counter.end())
            tag_counter.insert(pair<std::string, int>(*it, 1));
        else
            ++tag_counter[*it];
    }
    ques_fd<<'\n';
    
}

void
proc_answer(string s)
{
    xml_document<> doc;
    doc.parse<0>(&s[0]);
    
    int pid = atoi(doc.first_node()->first_attribute("ParentId")->value());
    int uid = get_uid(&doc);
    int score = atoi(doc.first_node()->first_attribute("Score")->value());

    ans_fd<<pid<<','<<uid<<','<<score<<'\n';
}


void 
process(string str)
{
    string post_type("PostTypeId");
    unsigned found = str.find(post_type);
    if (found<str.size()) {
        int type = str[found+post_type.length()+2] - 48;
        if (type == 1) {
            proc_question(str);
        }
        else if(type == 2) {
            proc_answer(str);
        }
    }
}

void
dump_qa(const char *f_name)
{
    boost::iostreams::mapped_file_source file;
    file.open(f_name);
    char *curr = (char*)file.data();
    char *pos = strchr(curr, '\n');
    while (pos)
    {
        int s = pos - curr;
        char line[s];
        memcpy(line, curr, s-1);
        line[s-1] = '\0';

        process(string(line));
        /* update pointer to the next line */ 
        curr = pos + 1;
        pos = strchr(curr, '\n');

    }

    file.close();
}

void
dump_tags()
{
    for(map<string, int>::iterator it = tag_counter.begin(); it!=tag_counter.end(); ++it)
        uniq_tags<<it->first<<','<<it->second<<'\n';

    uniq_tags.close();
}

int
main(int argc, char **argv)
{
    try {
        dump_qa(argv[1]);
        dump_tags();
    } catch (const char* s) {
        std::cout<<s<<std::endl;
    }
     
    
    ques_fd.close();
    ans_fd.close();
    return 0;
}
