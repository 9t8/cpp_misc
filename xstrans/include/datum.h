#ifndef NINTY8_MINI_PROJECTS_R5_INTERPRETER_DATUM_H
#define NINTY8_MINI_PROJECTS_R5_INTERPRETER_DATUM_H

#include <bits/stdc++.h>

struct datum {
  virtual operator std::string() const = 0;

  friend std::ostream &operator<<(std::ostream &os, const datum &d) {
    return os << static_cast<std::string>(d);
  }
};

struct list_datum : public datum {
  operator std::string() const override {
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

struct decimal_datum : public datum {
  decimal_datum(const double &v) : datum(), val(v) {}

  operator std::string() const override { return std::to_string(val) + "\n"; }

  double val;
};

struct id_datum : public datum {
  id_datum(const std::string &n) : name(n) {}

  operator std::string() const override { return name + "\n"; }

  std::string name;
};

#endif // header guard
