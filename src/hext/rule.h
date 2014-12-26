#ifndef HEXT_RULE_H
#define HEXT_RULE_H

#include <string>
#include <vector>
#include <memory>

#include <gumbo.h>

#include "hext/make-unique.h"
#include "hext/attribute.h"
#include "hext/match-tree.h"


namespace hext {


class rule
{
public:
  rule();

  void print(std::ostream& out = std::cout, int indent_level = 0) const;

  void append_child(const rule& r, int level = 0);
  void append_attribute(attribute attr);

  std::string get_tag_name() const;
  void set_tag_name(std::string name);

  void match_recursively(
    const GumboNode * node,
    match_tree * m
  ) const;

  void match_node_children(
    const GumboNode * node,
    match_tree * m
  ) const;

  bool matches(const GumboNode * node) const;

  std::unique_ptr<match_tree>
  capture(const GumboNode * node) const;

private:
  std::vector<rule> children;
  std::vector<attribute> attributes;

  std::string tag_name;
};  


} // namespace hext


#endif // HEXT_RULE_H

