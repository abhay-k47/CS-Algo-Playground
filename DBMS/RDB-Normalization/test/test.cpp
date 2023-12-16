#include "attribute_set_test.hpp"
#include "schema_test.hpp"
#include "normalizer_test.hpp"

int main(int argc, char const* argv[])
{
  AttributeSetTest::run();
  SchemaTest::run();
  NormalizerTest::run();
  return 0;
}
