

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

  void make_driftin_dragonfly() {
    _nodes = {{{1, "dis-be-me-head"}},
              {{2, "me"}, {5, "dis-be-me"}, {9, "dis-be-me"}},
              {{3, "long-tail"}},
              {{4, "be-dis"}},
              {},
              {{6, "front-right"}},
              {{7, "me-right"}},
              {{8, "back"}},
              {{2, "be-dis"}},
              {{10, "front-left"}},
              {{11, "and-left"}},
              {{12, "back"}},
              {{2, "be-dis"}}};
  }

  void make_slinky_star() {
    _nodes = {{}};
    _nodes.resize(15);
    for (int i(1); i < 15; i += 2) {
      _nodes[0].push_back({i, "-"});
      _nodes[i] = {{i + 1, "-"}};
    }
  }

  void make_kathy_da_grate() {
    _nodes.clear();
    _nodes.resize(15);
    for (int i(0); i < 5; ++i) {
      _nodes[i] = {{(i + 1) % 5, "-"}, {2 * i + 5, "-"}};
      _nodes[2 * i + 5] = {{2 * i + 6, "-"}};
    }
  }

  void make_dodos_in_space() {
    _nodes.clear();
    _nodes.resize(50);
    for (int i(0); i < 50; i += 2)
      _nodes[i] = {{i + 1, "Yippee-Dodo-#" + std::to_string(i)}};
  }

  void make_purty_pitcher() {
    _nodes.clear();
    int depth(3);
    _nodes.resize(2 * powl(3, depth - 1) + 1);
    sierpinski(depth, 0, 0);
  }

protected:
  friend class Tests;

  struct Edge {
    int _dst;
    std::string _tag;
  };

  std::vector<std::vector<Edge>> _nodes;

  void sierpinski(const int &depth, const int &link_root,
                  const int &node_root) {
    if (depth == 1) {
      _nodes[link_root] = {{node_root + 1, ""}, {node_root + 2, ""}};
      return;
    }
    sierpinski(depth - 1, link_root, node_root);
    int root_offset(powl(3, depth - 2));
    sierpinski(depth - 1, node_root + root_offset, node_root + 2 * root_offset);
    sierpinski(depth - 1, node_root + 2 * root_offset,
               node_root + 4 * root_offset);
  }
};
