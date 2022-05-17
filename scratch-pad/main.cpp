#include <bits/stdc++.h>

enum cat {
  ag,
  ca,
  cu,
  fe,
  sr,
  zn,
  pb,
  mn,
  al,
  ba,
  k,
  mg,
  na,
  nh4,
  sn,
  cr,
  co,
  ni
};

enum an { no3, cl, i, po4, cro4, oh, br, co3, so4, c2o4, c2h3o2 };

using compound = std::pair<cat, an>;

struct mix {
  const compound s0, s1;
  const bool p;
};

void table_to_list(const std::vector<compound> &rows,
                   const std::vector<compound> &cols,
                   const std::vector<std::vector<bool>> &table,
                   std::deque<mix> &list) {
  for (size_t row{}; row < rows.size(); ++row) {
    for (size_t col{}; col < cols.size(); ++col) {
      list.push_back({rows[row], cols[col], table[row][col]});
    }
  }
}

int main() {
  const std::vector<compound> s1_rows{
      {al, cl}, {ba, cl},  {k, i},     {k, po4},  {k, cro4},  {mg, cl},
      {na, oh}, {na, br},  {nh4, co3}, {na, so4}, {na, c2o4}, {na, c2h3o2},
      {sn, cl}, {cr, so4}, {co, cl},   {ni, cl}};

  const std::vector<compound> s1_cols{{ag, no3}, {ca, no3}, {cu, no3},
                                      {fe, no3}, {sr, no3}, {zn, no3},
                                      {pb, no3}, {mn, no3}};

  const std::vector<std::vector<bool>> s1_data{
      {1, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 1, 1},
      {1, 0, 1, 1, 0, 0, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 0, 1, 1, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 1, 0, 0, 0},
      {1, 1, 1, 0, 1, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 1, 0, 0, 1, 1}, {1, 0, 0, 1, 0, 1, 1, 1},
  };

  const std::vector<compound> s2_rows{
      {na, so4}, {na, oh}, {na, br}, {na, c2o4}, {na, c2h3o2}};

  const std::vector<compound> s2_cols{{k, cro4}, {k, i}, {k, po4}, {nh4, co3}};

  const std::vector<std::vector<bool>> s2_data(5, std::vector(4, false));

  const std::vector<compound> s3_rows{{al, cl}, {ba, cl}, {mg, cl}, {sn, cl},
                                      {co, cl}, {ni, cl}, {cr, so4}};

  const std::vector<compound> s3_cols{{k, cro4},  {k, i},       {k, po4},
                                      {na, so4},  {na, oh},     {na, br},
                                      {na, c2o4}, {na, c2h3o2}, {nh4, co3}};

  const std::vector<std::vector<bool>> s3_data{
      {1, 0, 1, 0, 1, 0, 0, 0, 0}, {1, 0, 1, 1, 1, 0, 1, 0, 1},
      {0, 0, 1, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
      {1, 1, 1, 0, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 1, 0, 0, 1, 1},
      {0, 0, 1, 0, 1, 1, 0, 0, 1}};

  std::deque<mix> mixes{mix{{}, {}, false}}; // 0 = "null" mix: used for given
  table_to_list(s1_rows, s1_cols, s1_data, mixes);
  table_to_list(s2_rows, s2_cols, s2_data, mixes);

  std::cout << "DONE\n";
}
