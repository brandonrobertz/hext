#ifndef HEXT_PATTERN_ATTRIBUTE_COUNT_MATCH_H_INCLUDED
#define HEXT_PATTERN_ATTRIBUTE_COUNT_MATCH_H_INCLUDED

#include "hext/pattern/Match.h"

#include <gumbo.h>


namespace hext {


/// Matches nodes that have a certain amount of attributes.
class AttributeCountMatch : public Match
{
public:
  explicit AttributeCountMatch(int attribute_count);

  /// Return true if node has attribute_count amount of attributes.
  bool matches(const GumboNode * node) const final;

private:
  int attribute_count_;
};


} // namespace hext


#endif // HEXT_PATTERN_ATTRIBUTE_COUNT_MATCH_H_INCLUDED

