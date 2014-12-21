#ifndef HEXT_PARSER_H
#define HEXT_PARSER_H

#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <stdexcept>

#include "hext/token.h"
#include "hext/lexer.h"
#include "hext/attribute.h"
#include "hext/rule.h"


namespace hext {
namespace parser {


class parse_error : public std::runtime_error
{
public:
  explicit parse_error(const char * msg);
};


void append_rule(
  std::vector<rule>::iterator begin,
  std::vector<rule>::iterator end,
  rule r,
  int level
);

std::vector<rule> 
parse_range(const char * begin, const char * end);

std::vector<rule>
parse_file(const char * path);


} // namespace parser
} // namespace hext


#endif // HEXT_PARSER_H

