#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "normalizer.hpp"
#include "schema.hpp"
#include <memory>
#include <vector>

class Database
{
public:
  void addSchema(const Schema& r);
  Database normalize(std::unique_ptr<Normalizer> normalizer) const;
  friend std::ostream& operator<<(std::ostream& os, const Database& db);

private:
  std::vector<Schema> schemas_;
};

#endif