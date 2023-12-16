#include "database.hpp"

void Database::addSchema(const Schema& schema)
{
  schemas_.push_back(schema);
}

Database Database::normalize(std::unique_ptr<Normalizer> normalizer) const
{
  Database newdb;
  for (auto schema : schemas_)
    for (auto newSchema : normalizer->normalize(schema))
      newdb.addSchema(newSchema);
  return newdb;
}

std::ostream& operator<<(std::ostream& os, const Database& db)
{
  for (auto schema : db.schemas_)
    os << schema;
  return os;
}
