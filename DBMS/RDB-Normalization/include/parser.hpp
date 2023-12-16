#ifndef PARSER_HPP
#define PARSER_HPP

#include "attribute_set.hpp"
#include <iostream>

class Parser
{
public:
  static AttributeSet parse(const std::string& s, char delim = ',');
};

#endif