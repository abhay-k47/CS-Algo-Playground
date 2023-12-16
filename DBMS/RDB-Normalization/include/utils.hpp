#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

bool isWhitespace(char c);
void trim(std::string& s);
std::vector<std::string> split(const std::string& s, char delim = ' ');

#endif