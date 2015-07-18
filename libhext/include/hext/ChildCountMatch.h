#ifndef HEXT_CHILD_COUNT_MATCH_H_INCLUDED
#define HEXT_CHILD_COUNT_MATCH_H_INCLUDED

#include "hext/Match.h"

#include <gumbo.h>


namespace hext {


/// Matches HTML elements that have a certain amount of children of type
/// element (exluding text nodes, document nodes and others).
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   GumboNode * none = ...; // <div>Text nodes are ignored</div>
///   GumboNode * two  = ...; // <ul><li>first</li><li>last</li></ul>
///
///   ChildCountMatch m_none(/* child count */ 0);
///   ChildCountMatch m_two (/* child count */ 2);
///
///   assert( m_none.matches(none));
///   assert(!m_none.matches(two));
///
///   assert( m_two.matches(two));
///   assert(!m_two.matches(none));
/// ~~~~~~~~~~~~~
class ChildCountMatch : public Match
{
public:
  /// Construct a ChildCountMatch that matches HTML elements with a child_count
  /// amount of children. If child_count is negative, child_count will be set to
  /// zero.
  explicit ChildCountMatch(int child_count);

  /// Return true if node has child_count amount of children.
  ///
  /// @param node:  A pointer to a GumboNode of type GUMBO_NODE_ELEMENT.
  bool matches(const GumboNode * node) const final;

private:
  /// Return amount of node's children that have node type GUMBO_NODE_ELEMENT.
  int count_child_elements(const GumboNode * node) const;

  /// The amount of children an HTML element must have in order to match.
  int child_count_;
};


} // namespace hext


#endif // HEXT_CHILD_COUNT_MATCH_H_INCLUDED

