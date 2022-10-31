#include "parse.h"

#include "datum.h"
#include "token.h"

#include <bits/stdc++.h>

std::unique_ptr<datum> parse(std::deque<std::unique_ptr<token>> &tokens) {
  assert(!tokens.empty() && "expected a token but none found");

  const auto &next_token_type(typeid(*tokens.front()));

  assert(next_token_type != typeid(endl_token) && "unexpected closing paren");

  if (next_token_type == typeid(beginl_token)) {
    std::unique_ptr<list_datum> p_list(new list_datum);
    tokens.pop_front();
    while (typeid(*tokens.front()) != typeid(endl_token)) {
      p_list->elements.push_back(parse(tokens));
    }
    tokens.pop_front();
    return p_list;
  }

  if (next_token_type == typeid(dec_token)) {
    std::unique_ptr<decimal_datum> p_fp(new decimal_datum(
        dynamic_cast<const dec_token &>(*tokens.front()).val));
    tokens.pop_front();
    return p_fp;
  }

  if (next_token_type == typeid(id_token)) {
    std::unique_ptr<id_datum> p_id(
        new id_datum(dynamic_cast<const id_token &>(*tokens.front()).name));
    tokens.pop_front();
    return p_id;
  }

  assert(0 && "unexpected token type");
}
