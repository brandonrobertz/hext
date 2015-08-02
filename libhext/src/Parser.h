#ifndef HEXT_PARSER_H_INCLUDED
#define HEXT_PARSER_H_INCLUDED

#include "hext/HtmlTag.h"
#include "hext/Rule.h"
#include "hext/SyntaxError.h"

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>

#include <boost/optional.hpp>
#include <boost/regex/regex_traits.hpp>
#include <boost/regex/pattern_except.hpp>


namespace hext {


/// Parses a string containing hext rule definitions.
///
/// @par Example:
/// ~~~~~~~~~~~~~
///   std::string hext_str("<a href={href}/>");
///   Parser p(hext_str.begin(), hext_str.end());
///   try {
///     Rule rule = p.parse();
///     // ... do sth. with rule ...
///   } catch( SyntaxError& e ) {
///     // e.what() will contain a detailed error message.
///   }
/// ~~~~~~~~~~~~~
class Parser
{
public:
  /// Constructs a Parser to parse hext rule definitions contained in
  /// range [begin, end). Pointers are non-owning and must stay valid until the
  /// last call to Parser::parse().
  Parser(const char * begin, const char * end) noexcept;

  ~Parser();
  Parser(Parser&&);
  Parser& operator=(Parser&&);

  /// Parses hext rule definition from the given range and returns the top level
  /// Rule. Throws SyntaxError with a detailed error message on invalid input.
  ///
  /// @throws SyntaxError
  std::unique_ptr<Rule> parse();

private:
  Parser(const Parser&) = delete;
  Parser& operator=(const Parser&) = delete;

  /// Throws SyntaxError with an error message marking an unexpected character.
  [[noreturn]]
  void throw_unexpected() const;

  /// Throws SyntaxError with an error message marking an invalid HTML tag.
  ///
  /// @param tag:  A string containing the name of an invalid HTML tag.
  [[noreturn]]
  void throw_invalid_tag(const std::string& tag) const;

  /// Throws SyntaxError with an error message marking an invalid regular
  /// expression.
  ///
  /// @param mark_len:  The length of the error marker.
  /// @param   e_code:  The error code given by boost::regex.
  [[noreturn]]
  void throw_regex_error(std::size_t                        mark_len,
                         boost::regex_constants::error_type e_code) const;

  /// Throws SyntaxError with an error message complaining about a missing
  /// closing tag.
  ///
  /// @param missing:  The HTML tag that was expected.
  [[noreturn]]
  void throw_missing_tag(HtmlTag missing) const;

  /// Throws SyntaxError with an error message marking an invalid closing tag.
  ///
  /// @param      tag: A string containing the invalid HTML closing tag.
  /// @param expected: The next expected closing HtmlTag. If empty, a closing
  ///                  tag was given but none expected.
  [[noreturn]]
  void throw_unexpected_tag(const std::string&       tag,
                            boost::optional<HtmlTag> expected) const;

  /// Prints an error at the current location within hext. Prints hext with line
  /// numbers up to the unexpected character.
  ///
  /// @param       uc:  A pointer to the unexpected character.
  /// @param mark_len:  The length of the error marker.
  /// @param      out:  Where to put the error message.
  void print_error_location(const char *  uc,
                            std::size_t   mark_len,
                            std::ostream& out) const;

  /// The beginning of the hext input as given in the constructor.
  const char * p_begin_;

  /// The current character that ragel is processing within the hext input.
  const char * p;

  /// The end of the hext input as given in the constructor.
  const char * pe;

  /// The end of the hext input. Same as Parser::pe.
  const char * eof;

  /// Ragel's current state.
  int cs;
};


} // namespace hext


#endif // HEXT_PARSER_H_INCLUDED
