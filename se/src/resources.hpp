#ifndef RESOURCES_HPP_INCLUDED
#define RESOURCES_HPP_INCLUDED
#include<string>
#include<vector>
#include<rapidxml/rapidxml.hpp>

std::string readf(const char *);
int get_uid(rapidxml::xml_document<> *);
std::vector<std::string> s_tags(char *);

#endif
