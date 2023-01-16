

#pragma once

#include <bits/stdc++.h>

class Hanoi {
 public:
  std::string solve(int num_discs, int src, int dst, int tmp) {
    return "# Below, 'A->B' means 'move the top disc on pole A to pole B'\n" +
           get_moves(num_discs, src, dst, tmp);
  }

 private:
  friend class Tests;

  std::vector<std::vector<std::vector<std::string>>> _cache;

  std::string lookup_moves(int num_discs, int src, int dst) {
    try {
      return _cache.at(num_discs).at(src).at(dst);
    } catch (const std::out_of_range &e) {
      return "";
    }
  }

  std::string get_moves(int num_discs, int src, int dst, int tmp) {
    if (num_discs == 0) return "";

    if (static_cast<int>(_cache.size()) <= num_discs)
      _cache.resize(num_discs + 1);

    if (static_cast<int>(_cache[num_discs].size()) <= src)
      _cache[num_discs].resize(src + 1);

    if (static_cast<int>(_cache[num_discs][src].size()) <= dst)
      _cache[num_discs][src].resize(dst + 1);

    if (_cache[num_discs][src][dst].empty())
      _cache[num_discs][src][dst] =
          get_moves(num_discs - 1, src, tmp, dst) + std::to_string(src) + "->" +
          std::to_string(dst) + "\n" + get_moves(num_discs - 1, tmp, dst, src);

    _cache[num_discs - 1].clear();
    return _cache[num_discs][src][dst];
  }
};
