// r3rs interpreter with boost for numeric tower

#include "lex.h"
#include "parse.h"

#include <iostream>

int main() {
  std::deque<std::unique_ptr<token>> tokens;
  lex(std::cin, tokens);

  while (!tokens.empty()) {
    std::unique_ptr<datum> p_ast(parse(tokens));
    std::cerr << "===-- begin new datum --===\n" << *p_ast;
  }
}
