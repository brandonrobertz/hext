#include "hext/test/Equals.h"

#include <utility>


namespace hext {
namespace test {


Equals::Equals(std::string literal)
: lit_(std::move(literal))
{
}

bool Equals::operator()(const char * subject) const
{
  return subject && this->lit_.compare(subject) == 0;
}


} // namespace test
} // namespace hext

