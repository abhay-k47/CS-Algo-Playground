#include "normalizer.hpp"
#include <iostream>
#include <memory>

class NormalizerTest
{
public:
  static void run()
  {
    std::cout << std::string(50, '-') << std::endl;
    {
      std::string rname{"TestSchema"};
      AttributeSet R{"A", "B", "C", "D", "E"};
      DependencySet deps;
      deps.add(Dependency(AttributeSet{"A"}, AttributeSet{"B"}));
      deps.add(Dependency(AttributeSet{"B", "C"}, AttributeSet{"D"}));
      Schema r{rname, R, deps};
      std::cout << r << std::endl;
      std::cout << "BCNF Decomposition" << std::endl;
      for (auto ri : std::make_unique<NormalizerBCNF>()->normalize(r))
        std::cout << ri << std::endl;
    }
    {
      std::string rname{"TestSchema"};
      AttributeSet R{"A", "B", "C", "D", "E", "G"};
      DependencySet deps;
      deps.add(Dependency(AttributeSet{"A"}, AttributeSet{"B", "C", "D"}));
      deps.add(Dependency(AttributeSet{"B", "C"}, AttributeSet{"D", "E"}));
      deps.add(Dependency(AttributeSet{"B"}, AttributeSet{"D"}));
      deps.add(Dependency(AttributeSet{"D"}, AttributeSet{"A"}));
      Schema r{rname, R, deps};
      std::cout << r << std::endl;
      std::cout << "3NF Decomposition" << std::endl;
      for (auto ri : std::make_unique<Normalizer3NF>()->normalize(r))
        std::cout << ri << std::endl;
    }
    std::cout << std::string(50, '-') << std::endl;
  }
};