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

#endif
