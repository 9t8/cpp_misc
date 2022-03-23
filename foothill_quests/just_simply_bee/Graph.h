

#pragma once

#include <bits/stdc++.h>

class Graph {
public:
  void make_silly_snake() {
    _nodes = {{{1, "i-see"}},      {{2, "the-silly-snake"}}, {{3, "i-be"}},
              {{4, "you-saw-me"}}, {{5, "once-like"}},       {{0, "kekule"}}};
  }

  void make_mr_sticky() {
    _nodes = {{{1, "."}}, {{2, "."}, {3, "."}, {4, "."}}, {},
              {},         {{5, "."}, {6, "."}},           {},
              {}};
  }

  void make_driftin_dragonfly() { _nodes = {}; }

  void make_slinky_star() { _nodes = {}; }

  void make_kathy_da_grate() { _nodes = {}; }

  void make_dodos_in_space() { _nodes = {}; }

  void make_purty_pitcher() { _nodes = {}; }

protected:
  friend class Tests;

  struct Edge {
    int _dst;
    std::string _tag;
  };

  std::vector<std::vector<Edge>> _nodes;

  // Suggested private helpers. Not tested.

  void add_edge(int src, int dst, std::string tag);

  std::string to_string() const;
};
