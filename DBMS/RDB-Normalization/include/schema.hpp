#ifndef SCHEMA_HPP
#define SCHEMA_HPP

#include "attribute_set.hpp"
#include "dependency_set.hpp"

class Schema
{
public:
  Schema(const std::string& name, const AttributeSet& R, const DependencySet& deps);
  DependencySet closure() const;
  std::vector<AttributeSet> getSuperKeys() const;
  std::vector<AttributeSet> getCandidateKeys() const;
  friend std::ostream& operator<<(std::ostream& os, const Schema& r);
  friend class Normalizer2NF;
  friend class Normalizer3NF;
  friend class NormalizerBCNF;
  friend class Normalizer4NF;

private:
  std::string name_;
  AttributeSet R_;
  DependencySet deps_;
};

#endif
