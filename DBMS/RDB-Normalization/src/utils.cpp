#include "utils.hpp"
#include <sstream>

bool isWhitespace(char c)
{
  return c == ' ' || c == '\t' || c == '\n';
}

void trim(std::string& s)
{
  while (!s.empty() && isWhitespace(s.back()))
    s.pop_back();
  while (!s.empty() && isWhitespace(s.front()))
    s = s.substr(1);
}

std::vector<std::string> split(const std::string& s, char delim)
{
  std::stringstream sin(s);
  std::string word;
  std::vector<std::string> res;
  while (getline(sin, word, delim))
  {
    trim(word);
    if (!word.empty())
      res.push_back(word);
  }
  return res;
}
