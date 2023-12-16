#ifndef NORMALIZER_HPP
#define NORMALIZER_HPP

#include "schema.hpp"
#include <vector>

class Normalizer
{
public:
  virtual std::vector<Schema> normalize(const Schema& r) const = 0;
  virtual bool test(const Schema& r) const = 0;
};

class Normalizer2NF : public Normalizer
{
public:
  std::vector<Schema> normalize(const Schema& r) const override;
  bool test(const Schema& r) const override;
};

class Normalizer3NF : public Normalizer
{
public:
  std::vector<Schema> normalize(const Schema& r) const override;
  bool test(const Schema& r) const override;
};

class NormalizerBCNF : public Normalizer
{
public:
  std::vector<Schema> normalize(const Schema& r) const override;
  bool test(const Schema& r) const override;
};

class Normalizer4NF : public Normalizer
{
public:
  std::vector<Schema> normalize(const Schema& r) const override;
  bool test(const Schema& r) const override;
};

#endif
