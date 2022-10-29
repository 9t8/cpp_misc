#ifndef NINTY8_MINI_PROJECTS_R5_INTERPRETER_DATUM_H
#define NINTY8_MINI_PROJECTS_R5_INTERPRETER_DATUM_H

#include <bits/stdc++.h>

struct datum {
  virtual operator std::string() const = 0;

  friend std::ostream &operator<<(std::ostream &os, const datum &d) {
    return os << static_cast<std::string>(d);
  }
};

struct list : public datum {
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

struct fp_datum : public datum {
  fp_datum(const double &v) : datum(), val(v) {}

  operator std::string() const override { return std::to_string(val) + "\n"; }

  double val;
};

#endif
