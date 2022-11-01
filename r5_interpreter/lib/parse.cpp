#include "parse.h"

#include "datum.h"
#include "token.h"

#include <bits/stdc++.h>

token_type find_next_token_type(std::deque<std::unique_ptr<token>> &tokens) {
  assert(!tokens.empty() && "find_next_token_type: expected a token but none "
                            "found (too many opening parens?)");

  const std::type_info &next_token_type(typeid(*tokens.front()));
  if (next_token_type == typeid(beginl_token)) {
    return token_type::beginl;
  }
  if (next_token_type == typeid(endl_token)) {
    return token_type::endl;
  }
  if (next_token_type == typeid(decimal_token)) {
    return token_type::decimal;
  }
  if (next_token_type == typeid(id_token)) {
    return token_type::id;
  }
  assert(0 && "find_next_token_type: unexpected token type");
}

std::unique_ptr<datum> parse(std::deque<std::unique_ptr<token>> &tokens) {
  token_type next_token_type(find_next_token_type(tokens));

  switch (next_token_type) {
  case token_type::none: {
    assert(0 && "parse: unexpected token type");
  }

  case token_type::endl: {
    assert(0 && "parse: unexpected end of list token");
  }

  case token_type::beginl: {
    std::unique_ptr<list_datum> p_list(new list_datum);
    tokens.pop_front();
    while (find_next_token_type(tokens) != token_type::endl) {
      p_list->elements.push_back(parse(tokens));
    }
    tokens.pop_front();
    return p_list;
  }

  case token_type::decimal: {
    std::unique_ptr<decimal_datum> p_fp(new decimal_datum(
        dynamic_cast<const decimal_token &>(*tokens.front()).val));
    tokens.pop_front();
    return p_fp;
  }

  case token_type::id: {
    std::unique_ptr<id_datum> p_id(
        new id_datum(dynamic_cast<const id_token &>(*tokens.front()).name));
    tokens.pop_front();
    return p_id;
  }
  }

  assert(0 && "parse: reached end of function");
}
