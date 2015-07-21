#include "hext/TextNodeMatch.h"

#include <cassert>


namespace hext {


bool TextNodeMatch::matches(const GumboNode * node) const noexcept
{
  assert(node);
  return ( node && node->type == GUMBO_NODE_TEXT );
}


} // namespace hext

