#include "database.hpp"
#include "normalizer.hpp"
#include "parser.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>

Database readDatabase()
{
  Database db;
  std::cout << "Enter all schemas in the database" << std::endl;
  std::string more_schemas, more_deps, input;
  do
  {
    std::string name;
    std::cout << "Enter name of schema: ";
    std::getline(std::cin, name);
    std::cout << "Enter schema: ";
    std::getline(std::cin, input);
    auto R = Parser::parse(input);
    DependencySet deps;
    do
    {
      std::cout << "Does this schema has more functional dependencies? [y/n] " << std::endl;
      std::getline(std::cin, more_deps);
      trim(more_deps);
      if (more_deps == "y")
      {
        std::cout << "Alpha: ";
        std::getline(std::cin, input);
        auto alpha = Parser::parse(input);
        std::cout << "Beta: ";
        std::getline(std::cin, input);
        auto beta = Parser::parse(input);
        deps.add(Dependency(alpha, beta));
      }
    } while (more_deps == "y");
    db.addSchema(Schema(name, R, deps));
    std::cout << "Do you have more schemas? [y/n] " << std::endl;
    std::getline(std::cin, more_schemas);
    trim(more_schemas);
  } while (more_schemas == "y");
  return db;
}

int main(int argc, char const* argv[])
{
  auto db = readDatabase();
  std::cout << db << std::endl;

  auto db2nf = db;
  db2nf.normalize(std::make_unique<Normalizer2NF>());
  std::cout << db2nf << std::endl;

  auto db3nf = db;
  db3nf.normalize(std::make_unique<Normalizer3NF>());
  std::cout << db3nf << std::endl;

  auto db4nf = db;
  db4nf.normalize(std::make_unique<Normalizer4NF>());
  std::cout << db4nf << std::endl;

  auto dbbcnf = db;
  dbbcnf.normalize(std::make_unique<NormalizerBCNF>());
  std::cout << dbbcnf << std::endl;

  return 0;
}
