#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>

using namespace std;

ifstream sorted_tags("./data/tags_sorted", fstream::out);
ifstream answers("./data/answers_u_sorted", fstream::out);
ifstream questions("./data/questions", fstream::out);

ofstream usr_matrix("./data/usr_matrix", fstream::in | fstream::trunc);
ofstream top_tags("./data/top_tags", fstream::in | fstream::trunc);


map<string, int> all_tags;              //all tags with their relative position
map<string, string> q;              //load all questions with tags here
int *features;
int f_size = 0;

void 
load_ques()
{
    string line; 
    while(getline(questions, line)) {
        stringstream ss(line);
        string id, rest;
        getline(ss, id, ',');
        getline(ss, rest, '\n');
        q.insert(pair<string, string>(id, rest));
    }
}

void
read_tags()
{
    string line;
    int count = 0;
    features = (int*) malloc(sizeof(int) * f_size);

    while(count < f_size) {
        getline(sorted_tags, line);
        stringstream ss(line);
        string cell;
        getline(ss, cell, ',');
        all_tags.insert(pair<string, int>(cell, count++));
        top_tags<<cell<<"\n";
    }
}

vector<string>
find_tags(string pid)
{
   vector<string> tags;
   string s(q.find(pid)->second);
   stringstream ss(s);
   getline(ss, s, ',');
   getline(ss, s, ',');
    
   string tag;
   while(getline(ss, tag, ',')) 
       tags.push_back(tag);

   return tags; 
}


void 
dump_features(string uid)
{

    usr_matrix<<uid<<",";
    for(int i=0; i<f_size; i++)
        usr_matrix<<features[i]<<',';
    usr_matrix<<"\n";
}

void 
insert_users()
{
    string line;
    string c_uid("0");
    int tag_index;

    while(getline(answers, line)) {
        stringstream ss(line);
        string cell;
        getline(ss, cell, ','); string pid = cell;
        getline(ss, cell, ','); string uid = cell;
        getline(ss, cell, ','); int score = atoi(cell.c_str());
        
        if(c_uid != uid) {
            /* fill the user matrix file */
            dump_features(c_uid);
            
            /* reset user features */
            fill_n(features, f_size, 0);
            c_uid.assign(uid);
        }

        if(score==0) {
            continue;
        }
        else {
            vector<string> tags = find_tags(pid);

            for(vector<string>::iterator it=tags.begin(); it!=tags.end(); ++it) {
                if(all_tags.find(*it) != all_tags.end()) {
                    tag_index = all_tags.find(*it)->second;
                    features[tag_index] += score;
                }
            }
        }
    }
    dump_features(c_uid);
}

void
close_fds()
{
    sorted_tags.close();
    answers.close();
    questions.close();
    usr_matrix.close();
    top_tags.close();
}



int
main(int argc, char **argv)
{
    f_size = atoi(argv[1]);
    read_tags();
    load_ques();
    insert_users();
    close_fds();
    return 0;
}

