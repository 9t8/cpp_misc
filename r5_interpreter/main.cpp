#include "datum.h"
#include "token.h"

#include <bits/stdc++.h>

void lex(std::istream &in, std::deque<std::unique_ptr<token>> &tokens) {
  for (;;) {
    in >> std::ws;

    if (in.eof())
      return;

    if (in.peek() == '(') {
      in.get();
      tokens.push_back(std::unique_ptr<begin_list>(new begin_list));
      continue;
    }

    if (in.peek() == ')') {
      in.get();
      tokens.push_back(std::unique_ptr<end_list>(new end_list));
      continue;
    }

    double val;
    in >> val;
    tokens.push_back(std::unique_ptr<fp_token>(new fp_token(val)));
  }
}

std::unique_ptr<datum> parse(std::deque<std::unique_ptr<token>> &tokens) {
  assert(!tokens.empty() && "expected a token but none found");

  assert(typeid(*tokens.front()) != typeid(end_list) &&
         "unexpected closing paren");

  if (typeid(*tokens.front()) == typeid(begin_list)) {
    std::unique_ptr<list> p_list(new list);
    tokens.pop_front();
    while (typeid(*tokens.front()) != typeid(end_list)) {
      p_list->elements.push_back(parse(tokens));
    }
    tokens.pop_front();
    return p_list;
  }

  if (typeid(*tokens.front()) == typeid(fp_token)) {
    std::unique_ptr<fp_datum> p_fp(
        new fp_datum(dynamic_cast<const fp_token &>(*tokens.front()).val));
    tokens.pop_front();
    return p_fp;
  }

  assert(0 && "unexpected token type");
}

int main() {
  std::deque<std::unique_ptr<token>> tokens;
  lex(std::cin, tokens);

  tokens.push_front(std::unique_ptr<begin_list>(new begin_list));
  tokens.push_back(std::unique_ptr<end_list>(new end_list));
  std::unique_ptr<datum> p_ast(parse(tokens));
  assert(tokens.empty() && "unexpected token");

  std::cerr << *p_ast;
}
