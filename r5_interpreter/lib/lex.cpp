#include "lex.h"

#include "token.h"

#include <bits/stdc++.h>

token_type find_next_token_type(std::istream &in) {
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
    return token_type::decimal;
  }

  default: {
    return token_type::id;
  }
  }
}

void lex(std::istream &in, std::deque<std::unique_ptr<token>> &tokens) {
  for (;;) {
    in >> std::ws;

    switch (find_next_token_type(in)) {
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

    case token_type::decimal: {
      double val;
      in >> val;
      tokens.push_back(std::unique_ptr<dec_token>(new dec_token(val)));
    } break;

    case token_type::id: {
      std::ostringstream name;

      for (;;) {
        switch (in.peek()) {
        case '(': {
          assert(0 && "illegal character in identifier: (");
        }

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
