#include "dependency.hpp"
#include <iostream>

Dependency::Dependency(const AttributeSet& alpha, const AttributeSet& beta)
    : alpha{alpha}
    , beta{beta}
{
}

std::ostream& operator<<(std::ostream& os, const Dependency& a)
{
  os << a.alpha << " -> " << a.beta;
  return os;
}
