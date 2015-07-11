#ifndef HEXT_PATTERN_TEXT_NODE_MATCH_H_INCLUDED
#define HEXT_PATTERN_TEXT_NODE_MATCH_H_INCLUDED

#include "hext/pattern/Match.h"

#include <gumbo.h>


namespace hext {


/// A TextNodeMatch is a Match that matches text nodes.
class TextNodeMatch : public Match
{
public:
  /// Return true if node is a text node.
  bool matches(const GumboNode * node) const final;
};


} // namespace hext


#endif // HEXT_PATTERN_TEXT_NODE_MATCH_H_INCLUDED

