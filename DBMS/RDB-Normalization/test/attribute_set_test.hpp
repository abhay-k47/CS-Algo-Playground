#include "attribute_set.hpp"
#include <iostream>

class AttributeSetTest
{
public:
  static void run()
  {
    std::cout << std::string(50, '-') << std::endl;
    AttributeSet as1{"a", "b", "c", "d", "g"};
    AttributeSet as2{"a", "b", "c", "d", "e", "f"};
    std::cout << "as1: " << as1 << std::endl;
    std::cout << "as2: " << as2 << std::endl;
    std::cout << "as1-as2: " << as1 - as2 << std::endl;
    std::cout << "as1+as2: " << as1 + as2 << std::endl;
    std::cout << "as1*as2: " << as1 * as2 << std::endl;
    std::cout << std::string(50, '-') << std::endl;
  }
};