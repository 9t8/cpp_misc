#ifndef NINTY8_MINI_PROJECTS_R5_INTERPRETER_TOKEN_H
#define NINTY8_MINI_PROJECTS_R5_INTERPRETER_TOKEN_H

#include <ostream>

enum class token_type { none, beginl, endl, id, decimal };

struct token {
  virtual operator std::string() const = 0;

  friend std::ostream &operator<<(std::ostream &os, const token &t) {
    return os << static_cast<std::string>(t);
  }
};

struct beginl_token : public token {
  operator std::string() const override { return "("; }
};

struct endl_token : public token {
  operator std::string() const override { return ")"; }
};

struct decimal_token : public token {
  decimal_token(const double &v) : val(v) {}

  operator std::string() const override { return std::to_string(val); }

  double val;
};

struct id_token : public token {
  id_token(const std::string &n) : name(n) {}

  operator std::string() const override { return name + "\n"; }

  std::string name;
};

#endif // header guard
