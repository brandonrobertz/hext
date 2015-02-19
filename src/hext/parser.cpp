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
, bf(nullptr)
, attr_name()
, cap_var()
, cap_regex()
{
}

std::unique_ptr<match_pattern>
create_match_pattern(const token& tok, const state& st)
{
  std::unique_ptr<attr_test> test;
  if( tok.tid == TK_MATCH_REGEX )
    test = make_unique<regex_test>(tok.to_string());
  else
    test = make_unique<literal_test>(tok.to_string());

  if( st.bf )
    return make_unique<builtin_match>(st.bf, std::move(test));
  else
    return make_unique<attribute_match>(st.attr_name, std::move(test));
}

std::unique_ptr<capture_pattern>
create_capture_pattern(const state& st)
{
  if( st.bf )
    return make_unique<builtin_capture>(st.cap_var, st.bf, st.cap_regex);
  else
    return make_unique<attribute_capture>(
      st.cap_var, st.attr_name, st.cap_regex
    );
}

std::vector<rule> parse_range(const char * begin, const char * end)
{
  lexer lex(begin, end);
  std::vector<token> tokens = lex.lex();
  rule_builder builder;
  std::vector<rule> rules;
  state st;

  for( const auto& tok : tokens )
  {
    // we expect the lexer to have catched all syntax errors
    switch( tok.tid )
    {
      case TK_NEWLINE:
      case TK_EOF:
        if( st.rule_start )
        {
          rule r = builder.build_and_reset();
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
        builder.set_direct_descendant(true);
        break;
      case TK_NTH_CHILD:
        builder.set_nth_child(std::stoi(tok.to_string()));
        break;
      case TK_TAG_NAME:
        builder.set_tag_name(tok.to_string());
        break;
      case TK_BUILTIN_NAME:
        st.bf = bi::get_builtin_by_name(tok.to_string());
        if( !st.bf )
          throw parse_error("Unknown builtin '" + tok.to_string() + "'");
        break;
      case TK_ATTR_NAME:
        st.attr_name = tok.to_string();
        break;
      case TK_MATCH_LITERAL:
        /* don't break, let through */
      case TK_MATCH_REGEX:
        builder.append_match_pattern(create_match_pattern(tok, st));
        st.bf = nullptr;
        break;
      case TK_CAP_END:
        builder.append_capture_pattern(create_capture_pattern(st));
        // For every attribute-capture also insert a match-pattern
        // that checks if the attribute actually exists.
        if( !st.bf )
        {
          builder.append_match_pattern(make_unique<attribute_match>(
            st.attr_name, std::unique_ptr<attr_test>(nullptr)
          ));
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
        builder.set_closed(true);
        break;
      case TK_RULE_BEGIN:
        st.rule_start = true;
        break;
      case TK_ERROR:
        throw parse_error("syntax error");
      default:
        throw parse_error("unknown token");
    }
  }

  return rules;
}


} // namespace parser
} // namespace hext

