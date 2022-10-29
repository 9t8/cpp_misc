#include <bits/stdc++.h>

#include "datum.h"
#include "token.h"

token_type get_next_token_type(std::istream &in) {
  switch (in.peek()) {
  case std::istream::traits_type::eof(): {
    return token_type::none;
  }

  case '(': {
    return token_type::beginl;
  }

  case ')': {
    return token_type::endl;
  }

  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '.':
  case '+':
  case '-': {
    return token_type::dec;
  }

  default: {
    return token_type::id;
  }
  }
}

void lex(std::istream &in, std::deque<std::unique_ptr<token>> &tokens) {
  for (;;) {
    in >> std::ws;

    switch (get_next_token_type(in)) {
    case token_type::none: {
      return;
    }

    case token_type::beginl: {
      in.get();
      tokens.push_back(std::unique_ptr<beginl_token>(new beginl_token));
    } break;

    case token_type::endl: {
      in.get();
      tokens.push_back(std::unique_ptr<endl_token>(new endl_token));
    } break;

    case token_type::dec: {
      double val;
      in >> val;
      tokens.push_back(std::unique_ptr<dec_token>(new dec_token(val)));
    } break;

    case token_type::id: {
      std::ostringstream name;

      for (;;) {
        switch (in.peek()) {
        case '(':
        case ')':
        case ' ':
        case '\n':
        case std::istream::traits_type::eof(): {
          goto lex_id_loop_end;
        }

        default: {
          name << static_cast<char>(in.get());
        }
        }
      }
    lex_id_loop_end:

      tokens.push_back(std::unique_ptr<id_token>(new id_token(name.str())));
    } break;
    }
  }
}

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
    std::unique_ptr<dec_datum> p_fp(
        new dec_datum(dynamic_cast<const dec_token &>(*tokens.front()).val));
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

int main() {
  std::deque<std::unique_ptr<token>> tokens;
  lex(std::cin, tokens);

  tokens.push_front(std::unique_ptr<beginl_token>(new beginl_token));
  tokens.push_back(std::unique_ptr<endl_token>(new endl_token));
  std::unique_ptr<datum> p_ast(parse(tokens));
  assert(tokens.empty() && "unexpected token");

  std::cerr << *p_ast;
}
