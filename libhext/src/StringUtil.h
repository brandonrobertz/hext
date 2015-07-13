#ifndef HEXT_STRING_UTIL_H_INCLUDED
#define HEXT_STRING_UTIL_H_INCLUDED

#include <cassert>
#include <cstdlib>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <iostream>
#include <iomanip>

#include <boost/tokenizer.hpp>


namespace hext {


/// Remove whitespace from beginning and end and collapse multiple whitespace
/// to a single space, as is expected when extracting text from html.
/// http://www.w3.org/TR/html5/infrastructure.html#strip-and-collapse-whitespace
///
/// Example:
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// "   Like\na Rolling\n\tStone  "
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// becomes
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// "Like a Rolling Stone"
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::string TrimAndCollapseWs(std::string str);

/// Check if given character is a space character according to the html spec.
/// std::isspace is not suitable, because it is locale aware.
/// http://www.w3.org/TR/html5/infrastructure.html#space-character
bool IsSpace(char c);

/// Return a visual representation for every char, including control
/// characters like the nullbyte.
std::string CharName(char c);

/// Convenience typedefs for CharPosition().
typedef std::iterator_traits<const char *>::difference_type CharPosType;
typedef std::pair<CharPosType, CharPosType> CharPosPair;

/// Return a pair<line_offset, character_offset> for the position of `c` after
/// `begin`. Numbering is zero-based.
CharPosPair CharPosition(const char * begin, const char * c);

/// Return width of number when printed as decimal.
int DecimalWidth(std::size_t number);

/// Return true if subject contains word. Word boundaries are the beginning and
/// end of subject, and spaces.
bool ContainsWord(const std::string& subject, const std::string& word);


} // namespace hext


#endif // HEXT_STRING_UTIL_H_INCLUDED
