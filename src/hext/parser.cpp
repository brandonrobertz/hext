#include "hext/parser.h"


namespace hext {
namespace parser {


parse_error::parse_error(const std::string& msg)
: std::runtime_error(msg)
{
}


state::state()
: rule_start(false)
, indent(0)
, tag_name()
, is_direct_desc(false)
, is_closed(false)
, nth_child(0)
, bf(nullptr)
, attr_name()
, cap_var()
, cap_regex()
, matchp()
, capturep()
{
}

std::unique_ptr<match_pattern>
create_match_pattern(const token& tok, const state& st)
{
  if( st.bf )
  {
    if( tok.tid == TK_MATCH_REGEX )
    {
      return std::unique_ptr<match_pattern>(
        new builtin_regex_match(
          st.bf, tok.to_string()
        )
      );
    }
    else
    {
      return std::unique_ptr<match_pattern>(
        new builtin_literal_match(
          st.bf, tok.to_string()
        )
      );
    }
  }
  else if( tok.tid == TK_MATCH_REGEX )
  {
    return std::unique_ptr<match_pattern>(
      new regex_match(st.attr_name, tok.to_string())
    );
  }
  else
  {
    return std::unique_ptr<match_pattern>(
      new literal_match(st.attr_name, tok.to_string())
    );
  }
}

std::unique_ptr<capture_pattern>
create_capture_pattern(const state& st)
{
  if( st.bf )
  {
    return std::unique_ptr<capture_pattern>(
      new builtin_capture(
        st.cap_var, st.bf, st.cap_regex
      )
    );
  }
  else
  {
    return std::unique_ptr<capture_pattern>(
      new attribute_capture(
        st.cap_var, st.attr_name, st.cap_regex
      )
    );
  }
}

std::vector<rule> parse_range(const char * begin, const char * end)
{
  lexer lex(begin, end);
  std::vector<token> tokens = lex.lex();
  std::vector<rule> rules;
  state st;

  for( const auto& tok : tokens )
  {
    // we expect the lexer to have catched all syntax errors
    switch( tok.tid )
    {
      case TK_NEWLINE:
        if( st.rule_start )
        {
          rule r(
            st.tag_name,
            st.is_direct_desc,
            st.is_closed,
            st.nth_child,
            rule_patterns(std::move(st.matchp), std::move(st.capturep))
          );
          // either top-level rule or first rule
          if( st.indent == 0 || rules.empty() )
            rules.push_back(std::move(r));
          else
            rules.back().append_child(std::move(r), st.indent);
          // reset parse state
          st = state();
        }
        st.indent = 0;
        break;
      case TK_INDENT:
        st.indent++;
        break;
      case TK_DIRECT_DESC:
        st.is_direct_desc = true;
        break;
      case TK_NTH_CHILD:
        st.nth_child = std::stoi(tok.to_string());
        break;
      case TK_TAG_NAME:
        st.tag_name = tok.to_string();
        break;
      case TK_BUILTIN_NAME:
        st.bf = bi::get_builtin_by_name(tok.to_string());
        if( !st.bf )
          throw parse_error(std::string("unknown builtin: ") + tok.to_string());
        break;
      case TK_ATTR_NAME:
        st.attr_name = tok.to_string();
        break;
      case TK_MATCH_LITERAL:
        /* don't break, let through */
      case TK_MATCH_REGEX:
        st.matchp.push_back(create_match_pattern(tok, st));
        st.bf = nullptr;
        break;
      case TK_CAP_END:
        st.capturep.push_back(create_capture_pattern(st));
        // For every attribute-capture also insert a match-pattern
        // that checks if the attribute actually exists.
        if( !st.bf )
        {
          std::unique_ptr<match_pattern> pm(
            new attribute_match(
              st.attr_name
            )
          );
          st.matchp.push_back(std::move(pm));
        }
        st.bf = nullptr;
        break;
      case TK_CAP_VAR:
        st.cap_var = tok.to_string();
        break;
      case TK_CAP_REGEX:
        st.cap_regex = tok.to_string();
        break;
      case TK_RULE_END:
        st.is_closed = true;
        break;
      case TK_RULE_BEGIN:
        st.rule_start = true;
        break;
      case TK_EOF:
        break;
      case TK_ERROR:
        throw parse_error("syntax error");
        break;
      default:
        throw parse_error("unknown token");
        break;
    }
  }

  return rules;
}

std::vector<rule> parse_file(const std::string& path)
{
  std::ifstream file;
  // force exception on error
  file.exceptions(std::ios::failbit | std::ios::badbit);
  file.open(path);

  std::string input(
    (std::istreambuf_iterator<char>(file)),
    std::istreambuf_iterator<char>()
  );
  const char * c_begin = input.c_str();
  const char * c_end = c_begin + input.size();

  return parse_range(c_begin, c_end);
}


} // namespace parser
} // namespace hext

