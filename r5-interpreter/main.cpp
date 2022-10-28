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

  friend std::ostream &operator<<(std::ostream &os, const datum &d) {
    return os << static_cast<std::string>(d);
  }
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
      oss << *e;
    }
    oss << ")\n";
    return oss.str();
  }

  std::deque<std::unique_ptr<datum>> elements;
};

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
