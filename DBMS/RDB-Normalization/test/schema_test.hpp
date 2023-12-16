#include "schema.hpp"
#include <iostream>

class SchemaTest
{
public:
  static void run()
  {
    std::cout << std::string(50, '-') << std::endl;
    std::string rname{"TestSchema"};
    AttributeSet R{"A", "B", "C", "D", "E"};
    DependencySet deps;
    deps.add(Dependency(AttributeSet{"A"}, AttributeSet{"B", "C", "D"}));
    deps.add(Dependency(AttributeSet{"B", "C"}, AttributeSet{"D", "E"}));
    deps.add(Dependency(AttributeSet{"B"}, AttributeSet{"D"}));
    deps.add(Dependency(AttributeSet{"D"}, AttributeSet{"A"}));
    Schema r{rname, R, deps};
    std::cout << r << std::endl;
    std::cout << "Super Keys" << std::endl;
    for (auto superkey : r.getSuperKeys())
      std::cout << superkey << std::endl;
    std::cout << "Candidate Keys" << std::endl;
    for (auto superkey : r.getCandidateKeys())
      std::cout << superkey << std::endl;
    std::cout << "Closure" << std::endl << r.closure() << std::endl;
    std::cout << "Canonical Cover" << std::endl << deps.canonicalCover() << std::endl;
    std::cout << std::string(50, '-') << std::endl;
  }
};