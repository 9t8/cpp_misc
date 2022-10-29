#ifndef NINTY8_MINI_PROJECTS_R5_INTERPRETER_TOKEN_H
#define NINTY8_MINI_PROJECTS_R5_INTERPRETER_TOKEN_H

#include <bits/stdc++.h>

struct token {
  virtual operator std::string() const = 0;

  friend std::ostream &operator<<(std::ostream &os, const token &t) {
    return os << static_cast<std::string>(t);
  }
};

struct begin_list : public token {
  operator std::string() const override { return "("; }
};

struct end_list : public token {
  operator std::string() const override { return ")"; }
};

struct string_token : public token {
  string_token(const std::string &v) : val(v) {}

  operator std::string() const override { return "#"; }

  std::string val;
};

struct fp_token : public token {
  fp_token(const double &v) : val(v) {}

  operator std::string() const override { return std::to_string(val); }

  double val;
};

#endif
