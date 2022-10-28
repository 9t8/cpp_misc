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
  fp_token(const double &v) : token(), val(v) {}

  virtual operator std::string() const { return std::to_string(val); }

  double val;
};

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

struct datum {
  virtual operator std::string() const = 0;
};

struct fp_datum : public datum {
  fp_datum(const double &v) : datum(), val(v) {}

  virtual operator std::string() const { return std::to_string(val) + "\n"; }

  double val;
};

struct list : public datum {
  virtual operator std::string() const {
    std::ostringstream oss;
    oss << "(\n";
    for (const auto &e : elements) {
      oss << static_cast<std::string>(*e);
    }
    oss << ")\n";
    return oss.str();
  }

  std::deque<std::unique_ptr<datum>> elements;
};

void parse(std::deque<std::unique_ptr<token>> &tokens, list &l) {
  assert(!tokens.empty() && "expected a token but none found");

  assert(typeid(*tokens.front()) != typeid(end_list) &&
         "unexpected closing paren");

  if (typeid(*tokens.front()) == typeid(begin_list)) {
    tokens.pop_front();
    l.elements.push_back(std::unique_ptr<list>(new list));
    while (typeid(*tokens.front()) != typeid(end_list)) {
      parse(tokens, dynamic_cast<list &>(*l.elements.back()));
    }
    tokens.pop_front();
    return;
  }

  if (typeid(*tokens.front()) == typeid(fp_token)) {
    l.elements.push_back(std::unique_ptr<fp_datum>(
        new fp_datum(dynamic_cast<const fp_token &>(*tokens.front()).val)));
    tokens.pop_front();
    return;
  }
}

int main() {
  std::deque<std::unique_ptr<token>> tokens;
  lex(std::cin, tokens);

  list l;
  tokens.push_front(std::unique_ptr<begin_list>(new begin_list));
  tokens.push_back(std::unique_ptr<end_list>(new end_list));
  parse(tokens, l);
  assert(tokens.empty() && "unexpected closing paren");

  std::cerr << static_cast<std::string>(l);
}
