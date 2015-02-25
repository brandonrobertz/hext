#ifndef HEXT_BUILTIN_MATCH_H
#define HEXT_BUILTIN_MATCH_H

#include <string>
#include <iostream>
#include <memory>

#include <gumbo.h>

#include "hext/pattern/match-pattern.h"
#include "hext/builtins.h"


namespace hext {


/// A BuiltinMatch is a MatchPattern that checks whether the result of a
/// builtin matches value_test.
class BuiltinMatch : public MatchPattern
{
public:
  BuiltinMatch(
    BuiltinFuncPtr f,
    std::unique_ptr<ValueTest> value_test
  );

  MatchResult matches(const GumboNode * node) const final;
  void print(std::ostream& out = std::cout) const final;

private:
  const BuiltinFuncPtr func_;
};


} // namespace hext


#endif // HEXT_BUILTIN_MATCH_H

