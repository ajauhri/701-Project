#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<map>
#include<rapidxml/rapidxml_print.hpp>
#include<boost/iostreams/device/mapped_file.hpp>
#include<resources.hpp>

using namespace std;
using namespace rapidxml;

ofstream ques_fd("../se-data/questions", fstream::app);
ofstream ans_fd("../se-data/answers", fstream::app);
ofstream uniq_tags("../se-data/tags", fstream::app);

map<string, int> tag_counter;

/**
 * proc_question - Processes a xml-format of a question and writes required params of a question in csv format
 **/
void 
proc_question(string s)
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
            tag_counter.insert(pair<string, int>(*it, 1));
        else
            ++tag_counter[*it];
    }
    ques_fd<<'\n';
}

/**
 * proc_answer - Processes a xml-format of an answer and writes essential parameters in csv format
 */
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
handle_qa(const char *f_name)
{
    boost::iostreams::mapped_file_source file;
    file.open(f_name);
    char *curr = (char*)file.data();
    char *pos = strchr(curr, '\n');

    /* for some reason, I like it */
    while (pos) {
        int s = pos - curr;       //get length of a line 
        char line[s];             //allocate space for the line 
        memcpy(line, curr, s-1);  //copy contents. s-1 as strschr points to the new line char
        line[s-1] = '\0';         //null terminate
        process(string(line));    //ready to be processed 

        /* update pointer to the next line */ 
        curr = pos + 1;           //move on to the next char
        pos = strchr(curr, '\n'); //search for the next new line
    }

    file.close();
}

void
handle_tags()
{
    for(map<string, int>::iterator it = tag_counter.begin(); it!=tag_counter.end(); ++it)
        uniq_tags<<it->first<<','<<it->second<<'\n';
    uniq_tags.close();
}

int
main(int argc, char **argv)
{
    try {
        handle_qa(argv[1]);
        handle_tags();
    } catch (const char* s) {
       cout<<s<<endl;
    }
     
    
    ques_fd.close();
    ans_fd.close();
    return 0;
}
