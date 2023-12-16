#ifndef DEPENDENCY_HPP
#define DEPENDENCY_HPP

#include "attribute_set.hpp"
#include <iostream>

class Dependency
{
public:
  AttributeSet alpha;
  AttributeSet beta;
  Dependency(const AttributeSet& alpha, const AttributeSet& beta);
  friend std::ostream& operator<<(std::ostream& os, const Dependency& a);
};

#endif