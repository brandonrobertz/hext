#ifndef HEXT_TEST_EQUALS_H_INCLUDED
#define HEXT_TEST_EQUALS_H_INCLUDED

#include "hext/test/ValueTest.h"

#include <string>


namespace hext {
namespace test {


/// Test whether another string equals a given literal.
class Equals : public ValueTest
{
public:
  explicit Equals(std::string literal);

  /// Return true if subject equals literal.
  bool operator()(const char * subject) const final;

private:
  std::string lit_;
};


} // namespace test
} // namespace hext


#endif // HEXT_TEST_EQUALS_H_INCLUDED

