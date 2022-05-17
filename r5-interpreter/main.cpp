#include <bits/stdc++.h>

struct token {
  virtual operator std::string() const = 0;

  friend std::ostream &operator<<(std::ostream &os, const token &t) {
    return os << static_cast<std::string>(t);
  }
};

struct begin_list : public token {
  virtual operator std::string() const { return "BEGIN_LIST"; }
};

struct end_list : public token {
  virtual operator std::string() const { return "END_LIST"; }
};

struct fp_token : public token {
  fp_token(const double &v) : token{}, val{v} {}

  virtual operator std::string() const { return std::to_string(val); }

  double val;
};

struct datum {
  virtual void eval() = 0;
};

struct fp_datum : public datum {
  fp_datum(const double &v) : datum{}, val{v} {}

  virtual void eval() {}

  double val;
};

struct list : public datum {
  virtual void eval() {}

  std::deque<std::unique_ptr<datum>> elements;
};

void lex(std::istream &in, std::deque<std::unique_ptr<token>> &tokens) {
  for (;;) {
    in >> std::ws;

    if (in.eof())
      return;

    if (in.peek() == '(') {
      in.get();
      tokens.push_back(std::unique_ptr<begin_list>{new begin_list});
      continue;
    }
    if (in.peek() == ')') {
      in.get();
      tokens.push_back(std::unique_ptr<end_list>{new end_list});
      continue;
    }
    double val;
    in >> val;
    tokens.push_back(std::unique_ptr<fp_token>{new fp_token{val}});
  }
}

// destroys tokens
void parse(std::deque<std::unique_ptr<token>> &tokens, list &l) {
  while (!tokens.empty()) {
    if (typeid(tokens.front()) == typeid(end_list)) {
      tokens.pop_front();
      return;
    }

    if (typeid(tokens.front()) == typeid(begin_list)) {
      tokens.pop_front();
      l.elements.push_back(
          std::unique_ptr<list>{std::unique_ptr<list>{new list}});
      parse(tokens, dynamic_cast<list &>(*l.elements.back()));

      break;
    }

    l.elements.push_back(std::unique_ptr<fp_datum>{
        new fp_datum{dynamic_cast<fp_token &>(*tokens.front()).val}});
    l.elements.pop_front();
  }
  throw;
}

int main() {
  std::deque<std::unique_ptr<token>> tokens;
  lex(std::cin, tokens);

  for (const std::unique_ptr<token> &t : tokens)
    std::cout << *t << '\n';

  list l;
  parse(tokens, l);
}
