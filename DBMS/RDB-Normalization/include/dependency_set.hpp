#ifndef DEPENDENCY_SET_HPP
#define DEPENDENCY_SET_HPP

#include "dependency.hpp"
#include <iostream>
#include <vector>

class DependencySet
{
public:
  void add(const Dependency& dep);
  AttributeSet closure(const AttributeSet& attrs) const;
  DependencySet canonicalCover() const;
  size_t size() const;
  Dependency& operator[](size_t idx);
  const Dependency& operator[](size_t idx) const;
  friend std::ostream& operator<<(std::ostream& os, const DependencySet& a);

private:
  std::vector<Dependency> deps_;
};

#endif