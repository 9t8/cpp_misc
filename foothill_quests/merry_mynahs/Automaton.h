

#pragma once

#include <bits/stdc++.h>

class Automaton {
public:
  static size_t pow_2(size_t n) { return size_t(1) << n; }

  static size_t translate_n_bits_starting_at(const std::vector<int> &bits,
                                             size_t pos, size_t n) {
    size_t result(0);
    for (n += pos; pos < n; ++pos)
      result = result << 1 | bits[pos];
    return result;
  }

  Automaton(size_t num_parents, size_t rule)
      : _num_parents(num_parents), _rules(1 << num_parents) {
    set_rule(rule);
  }

  bool equals(const Automaton &that) {
    return !_is_valid && !that._is_valid ||
           _is_valid && that._is_valid && _num_parents == that._num_parents &&
               _extreme_bit == that._extreme_bit && _rules == that._rules;
  }

  std::string generation_to_string(const std::vector<int> &gen, size_t width) {
    if (width % 2 == 0)
      return "";

    std::string result(width, _extreme_bit == 0 ? ' ' : '*');
    for (size_t i(0), offset((width - gen.size()) / 2); i < gen.size(); ++i) {
      result[i + offset] = gen[i] == 0 ? ' ' : '*';
    }
    return result;
  }

  bool set_rule(size_t rule) {
    if (rule >= 1 << _rules.size())
      return _is_valid = false;

    for (auto it(_rules.begin()); it < _rules.end(); ++it) {
      *it = rule & 1;
      rule <<= 1;
    }
    return _is_valid = true;
  }

  bool make_next_gen(const std::vector<int> &current_gen,
                     std::vector<int> &next_gen) {}

  bool _is_valid;
  size_t _num_parents;
  std::vector<bool> _rules;
  int _extreme_bit;
};
