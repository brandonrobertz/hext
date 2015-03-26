%%{
  machine hext;

  action error {
    this->throw_unexpected();
  }

  action act_newline {
    if( rule_start )
    {
      rule.consume_and_reset();
      rule_start = false;
    }
    else
    {
      rule.reset_indent();
    }
  }

  attr_name = ( alpha (alnum | '-' | '_')** );
  builtin_name = ( alpha (alnum | '-' | '_')** );
  cap_var = ( [^/{}][^/{}]** );
  match_literal = ( [^/{}"][^/{}"]** );
  cap_regex = ( ( [^/] | '\\/' )** );
  match_regex = ( ( [^/] | '\\/' )** );

  comment = (
    ' '*
    '#'
    (any - '\n')*
    (
      '\n' %act_newline
    )
  );

  nth_pattern = (
    (
      'even'
      %{
        rule.pattern().set_nth_pattern_multiplier("2");
        rule.pattern().set_nth_pattern_addend("0");
       }
    )
    |
    (
      'odd'
      %{
        rule.pattern().set_nth_pattern_multiplier("2");
        rule.pattern().set_nth_pattern_addend("1");
       }
    )
    |
    (
      (
        [0-9]+
        >{ LX_TK_START; }
        %{ LX_TK_STOP; rule.pattern().set_nth_pattern_multiplier(tok); }
      )
      (
        'n'
        %{ // '2n' must behave the same as '2n+0'.
           rule.pattern().set_nth_pattern_addend("0");
         }
        (
          '+'
          (
            [0-9]+
            >{ LX_TK_START; }
            %{ LX_TK_STOP; rule.pattern().set_nth_pattern_addend(tok); }
          )
        )?
      )?
    )
  );

  trait = (
    ':'
    (
      (
        ( 'empty' )
        %{ rule.pattern().consume_trait_child_count("0"); }
      )
      |
      (
        (
          'child-count('
          (
            [0-9]+
            >{ LX_TK_START; }
            %{ LX_TK_STOP; rule.pattern().consume_trait_child_count(tok); }
          )
          ')'
        )
      )
      |
      (
        ( 'nth-child(' nth_pattern ')' )
        %{ rule.pattern().consume_trait_nth_child(); }
      )
      |
      (
        ( 'nth-last-child(' nth_pattern ')' )
        %{
          rule.pattern().consume_trait_nth_child(NthChildMatch::OffsetOf::Back);
         }
      )
      |
      (
        ( 'nth-of-type(' nth_pattern ')' )
        %{
          rule.pattern().consume_trait_nth_child(
            NthChildMatch::OffsetOf::Front,
            rule.tag()
          );
         }
      )
      |
      (
        ( 'first-child' )
        %{
          rule.pattern().set_nth_pattern_multiplier("1");
          rule.pattern().consume_trait_nth_child();
         }
      )
      |
      (
        ( 'first-of-type' )
        %{
          rule.pattern().set_nth_pattern_multiplier("1");
          rule.pattern().consume_trait_nth_child(
            NthChildMatch::OffsetOf::Front,
            rule.tag()
          );
         }
      )
      |
      (
        ( 'last-child' )
        %{
          rule.pattern().set_nth_pattern_multiplier("1");
          rule.pattern().consume_trait_nth_child(NthChildMatch::OffsetOf::Back);
         }
      )
      |
      (
        ( 'last-of-type' )
        %{
          rule.pattern().set_nth_pattern_multiplier("1");
          rule.pattern().consume_trait_nth_child(
            NthChildMatch::OffsetOf::Back,
            rule.tag()
          );
         }
      )
      |
      (
        ( 'nth-last-of-type(' nth_pattern ')' )
        %{
          rule.pattern().consume_trait_nth_child(
            NthChildMatch::OffsetOf::Back,
            rule.tag()
          );
         }
      )
      |
      (
        ( 'only-child' )
        %{
          rule.pattern().set_nth_pattern_multiplier("1");
          rule.pattern().consume_trait_nth_child();
          rule.pattern().set_nth_pattern_multiplier("1");
          rule.pattern().consume_trait_nth_child(NthChildMatch::OffsetOf::Back);
         }
      )
    )
  );

  literal_value = (
    '"'
    (
      match_literal >{ LX_TK_START; }
                    %{ LX_TK_STOP;
                       rule.pattern().set_attr_literal(tok); }
    )
    '"'
  );

  attributes = 
    (
      ' '+
      (
        (
          (
            '@'
            (
              builtin_name
              >{ LX_TK_START; }
              %{ LX_TK_STOP;
                 {
                   if( !rule.pattern().set_builtin_function(tok) )
                     this->throw_unknown_token(tok, "builtin");
                 }
              }
            )
          )
          |
          (
            attr_name >{ LX_TK_START; }
                      %{ LX_TK_STOP; rule.pattern().set_attr_name(tok); }
          )
        )
        (
          (
            ( '^' | '*' | '!' | '~' | '$' )
            >{ rule.pattern().set_literal_operator(*this->p); }
            '=' literal_value
          )
          |
          (
            '='
            (
              (
                '{'
                (
                  cap_var >{ LX_TK_START; }
                          %{ LX_TK_STOP; rule.pattern().set_cap_var(tok); }
                )
                (
                  '/'
                  (
                    cap_regex >{ LX_TK_START; }
                              %{ LX_TK_STOP;
                                 try{ rule.pattern().set_cap_regex(tok); }
                                 catch( const boost::regex_error& e )
                                 { this->throw_regex_error(tok, e.code()); }
                               }
                  )
                  '/'
                )?
                '}'
              )
              |
              (
                (
                  '/'
                  (
                    match_regex >{ LX_TK_START; }
                                %{ LX_TK_STOP;
                                   try{ rule.pattern().set_attr_regex(tok); }
                                   catch( const boost::regex_error& e )
                                   { this->throw_regex_error(tok, e.code()); }
                                 }
                  )
                  '/'
                )
                |
                literal_value
              )
            )
          )
        )?
      ) %{ rule.pattern().consume_and_reset(); }
    )+;

  main := 
    ( 
      comment
      |
      (
        (
          '  ' %{ rule.increment_indent(); }
        )*
        (
          (
            '<'
            %{ rule_start = true; }
          )
          |
          (
            '>'
            %{
              rule_start = true;
              rule.set_any_descendant(true);
             }
          )
        )
        (
          '?' %{ rule.set_optional(true); }
        )?
        (
          attr_name >{ LX_TK_START; }
                    %{ LX_TK_STOP;
                       if( !rule.set_tag_name(tok) )
                         this->throw_unknown_token(tok, "html-tag"); }
        )?
        trait*
        attributes?
        (
          '>' %{ rule.set_closed(true); }
        )?
      )
      (
        '\n' %act_newline
      )?
    )**
    $err(error) $/act_newline $/{ fbreak; };
}%%
