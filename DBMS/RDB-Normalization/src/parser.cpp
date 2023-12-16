#include "parser.hpp"
#include "utils.hpp"

AttributeSet Parser::parse(const std::string& s, char delim)
{
  AttributeSet attrSet;
  for (auto attr : split(s, delim))
    attrSet.insert(attr);
  return attrSet;
}