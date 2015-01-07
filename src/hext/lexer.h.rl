#ifndef HEXT_LEXER_H
#define HEXT_LEXER_H

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "hext/token.h"
#include "hext/lexer-util.h"


namespace hext {


namespace ragel {
  %%{
    machine hext;
    include "hext.rl";
    write data;
  }%%
} // namespace ragel


/// lexer contains the ragel state machine and shields the user from its
/// details.
class lexer
{
public:
  /// Clang warns (-Wweak-vtables) that a vtable for lex_error may be placed
  /// in every translation unit, because lex_error doesn't have any
  /// 'out-of-line virtual method definitions', where it would normally put
  /// the vtable. But http://stackoverflow.com/a/23749273 suggests that this
  /// is a non-issue; the linker will clean it up.
  class lex_error : public std::runtime_error
  {
  public:
    explicit lex_error(const std::string& msg);
  };

  /// Setup ragel
  lexer(const char * begin, const char * end);

  /// Throws lexer::lex_error on invalid input (by calling lexer::throw_error)
  std::vector<token> lex();

private:
  /// Print diagnostics and throw lexer::lex_error.
  void throw_error() const;

  /// A pointer to the beginning of the overall input is needed to provide
  /// good error diagnostics.
  const char * p_begin;

  /// ragel's runtime state
  const char * p;
  const char * pe;
  const char * eof;
  int cs;
};


} // namespace hext


#endif // HEXT_LEXER_H

