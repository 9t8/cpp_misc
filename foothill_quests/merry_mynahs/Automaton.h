

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
      : _num_parents(num_parents), _rules(pow_2(num_parents)), _extreme_bit(0) {
    set_rule(rule);
  }

  bool equals(const Automaton &that) {
    return (!_is_valid && !that._is_valid) ||
           (_is_valid && that._is_valid && _num_parents == that._num_parents &&
            _extreme_bit == that._extreme_bit && _rules == that._rules);
  }

  std::string generation_to_string(const std::vector<int> &gen, size_t width) {
    if (width % 2 == 0)
      return "";

    std::string result(width, _extreme_bit == 0 ? ' ' : '*');
    for (size_t i(0), offset((width - gen.size()) / 2); i < gen.size(); ++i) {
      try {
        result.at(i + offset) = gen[i] == 0 ? ' ' : '*';
      } catch (const std::exception &e) {
      }
    }
    return result;
  }

  bool set_rule(size_t rule) {
    if (rule >= pow_2(_rules.size()))
      return _is_valid = false;

    for (auto it(_rules.begin()); it < _rules.end(); ++it) {
      *it = rule & 1;
      rule >>= 1;
    }
    return _is_valid = true;
  }

  bool make_next_gen(const std::vector<int> &current_gen,
                     std::vector<int> &next_gen) {
    if (!_is_valid)
      return false;

    if (current_gen.empty()) {
      next_gen = {1};
      return true;
    }

    if (current_gen.size() % 2 == 0) {
      return false;
    }

    next_gen.resize(current_gen.size() + _num_parents - 1);

    auto get_cell([&](const size_t &i) {
      try {
        return current_gen.at(i);
      } catch (const std::exception &e) {
        return _extreme_bit;
      }
    });

    for (size_t i(0); i < next_gen.size(); ++i) {
      size_t parent_value(0);
      for (int j(1 - _num_parents); j <= 0; ++j) {
        parent_value = parent_value << 1 | get_cell(i + j);
      }
      next_gen[i] = _rules[parent_value];
    }

    _extreme_bit = _rules[_extreme_bit * (_rules.size() - 1)];

    return true;
  }

  std::string get_first_n_generations(size_t n, size_t width) {
    if (width % 2 == 0)
      return "";

    std::string result;
    std::vector<int> cells;
    for (size_t i(0); i < n; ++i) {
      make_next_gen(cells, cells);
      result += generation_to_string(cells, width) + '\n';
    }
    return result;
  }

  bool _is_valid;
  size_t _num_parents;
  std::vector<bool> _rules;
  int _extreme_bit;
};
