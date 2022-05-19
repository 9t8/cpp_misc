#include <bits/stdc++.h>

//===-- class definitions --===

// clang-format off
enum cat { ag, ca, cu, fe, sr, zn, pb, mn, al, ba, k, mg, na, nh4, sn, cr, co, ni, num_cats };
// clang-format on

const std::array<std::string, num_cats> cat_names = {
    "ag", "ca", "cu", "fe", "sr",  "zn", "pb", "mn", "al",
    "ba", "k",  "mg", "na", "nh4", "sn", "cr", "co", "ni"};

enum an { no3, cl, i, po4, cro4, oh, br, co3, so4, c2o4, c2h3o2, num_ans };

const std::array<std::string, num_ans> an_names = {
    "no3", "cl",  "i",   "po4",  "cro4",  "oh",
    "br",  "co3", "so4", "c2o4", "c2h3o2"};

using compound = std::pair<const cat, const an>;

struct mix {
  const compound s0, s1;
  const bool p;
};

using evidence_table =
    std::array<std::array<std::deque<int>, num_ans>, num_cats>;

//===-- data --===

const std::vector<compound> s1_rows{
    {al, cl}, {ba, cl},  {k, i},     {k, po4},  {k, cro4},  {mg, cl},
    {na, oh}, {na, br},  {nh4, co3}, {na, so4}, {na, c2o4}, {na, c2h3o2},
    {sn, cl}, {cr, so4}, {co, cl},   {ni, cl}};

const std::vector<compound> s1_cols{{ag, no3}, {ca, no3}, {cu, no3}, {fe, no3},
                                    {sr, no3}, {zn, no3}, {pb, no3}, {mn, no3}};

// clang-format off
const std::vector<std::vector<bool>> s1_data{ // SET 1
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {1, 1, 1, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 1},
    {1, 0, 0, 1, 0, 1, 1, 1},
};
// clang-format on

const std::vector<compound> s2_rows{
    {na, so4}, {na, oh}, {na, br}, {na, c2o4}, {na, c2h3o2}};

const std::vector<compound> s2_cols{{k, cro4}, {k, i}, {k, po4}, {nh4, co3}};

const std::vector<std::vector<bool>> s2_data(5, std::vector(4, false)); // SET 2

const std::vector<compound> s3_rows{{al, cl}, {ba, cl}, {mg, cl}, {sn, cl},
                                    {co, cl}, {ni, cl}, {cr, so4}};

const std::vector<compound> s3_cols{{k, cro4},  {k, i},       {k, po4},
                                    {na, so4},  {na, oh},     {na, br},
                                    {na, c2o4}, {na, c2h3o2}, {nh4, co3}};

// clang-format off
const std::vector<std::vector<bool>> s3_data{ // SET 3
    {1, 0, 1, 0, 1, 0, 0, 0, 0},
    {1, 0, 1, 1, 1, 0, 1, 0, 1},
    {0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 1, 1, 1, 1},
    {0, 0, 1, 0, 1, 0, 0, 1, 1},
    {0, 0, 1, 0, 1, 1, 0, 0, 1},
};
// clang-format on

//===-- printing fns --===

std::ostream &operator<<(std::ostream &os, const cat &c) {
  return os << cat_names.at(c);
}

std::ostream &operator<<(std::ostream &os, const an &a) {
  return os << an_names.at(a);
}

std::ostream &operator<<(std::ostream &os, const compound &c) {
  return os << c.first << " " << c.second;
}

std::ostream &operator<<(std::ostream &os, const std::deque<int> &di) {
  for (const auto &i : di)
    os << " " << i;

  return os;
}

std::ostream &operator<<(std::ostream &os, const evidence_table &t) {
  os << "\t";
  for (int i{0}; i < num_ans; ++i)
    os << std::setw(8) << an_names[i];

  os << "\n";

  for (int i{0}; i < num_cats; ++i) {
    os << std::setw(8) << cat_names[i];
    for (int j{0}; j < num_ans; ++j)
      os << std::setw(8) << t[i][j].size();

    os << "\n";
  }

  return os;
}

//===-- high-level fns --===

void table_to_list(const std::vector<compound> &rows,
                   const std::vector<compound> &cols,
                   const std::vector<std::vector<bool>> &table,
                   std::deque<mix> &list) {
  for (size_t row{}; row < rows.size(); ++row) {
    for (size_t col{}; col < cols.size(); ++col) {
      if (rows[row].first != cols[col].first &&
          rows[row].second != cols[col].second)
        list.push_back({rows[row], cols[col], table[row][col]});
    }
  }
}

void gen_mix_list(std::deque<mix> &mixes) {
  mixes.push_back({{}, {}, false}); // mixes are 1-indexed, [0] used as delim
  table_to_list(s1_rows, s1_cols, s1_data, mixes);
  table_to_list(s2_rows, s2_cols, s2_data, mixes);
  table_to_list(s3_rows, s3_cols, s3_data, mixes);
}

void gen_soluble_evi(const std::deque<mix> &mixes,
                     evidence_table &soluble_evi) {
  for (size_t i{1}; i < mixes.size(); ++i) {
    if (!mixes[i].p) {
      soluble_evi[mixes[i].s0.first][mixes[i].s0.second].push_back(i);
      soluble_evi[mixes[i].s0.first][mixes[i].s1.second].push_back(i);
      soluble_evi[mixes[i].s1.first][mixes[i].s0.second].push_back(i);
      soluble_evi[mixes[i].s1.first][mixes[i].s1.second].push_back(i);
    }
  }
}

// TODO: maybe push more evidence: take advantage of delim
void gen_insol_evi(const std::deque<mix> &mixes,
                   const evidence_table &soluble_evi,
                   evidence_table &insol_evi) {
  for (size_t i{1}; i < mixes.size(); ++i) {
    if (mixes[i].p) {
      if (!soluble_evi[mixes[i].s0.first][mixes[i].s1.second].empty()) {
        insol_evi[mixes[i].s1.first][mixes[i].s0.second].push_back(i);
      }
      if (!soluble_evi[mixes[i].s1.first][mixes[i].s0.second].empty()) {
        insol_evi[mixes[i].s0.first][mixes[i].s1.second].push_back(i);
      }
    }
  }
}

void gen_contradictions(const evidence_table &soluble_evi,
                        const evidence_table &insol_evi,
                        std::deque<compound> &contradictions) {
  for (int i{0}; i < num_cats; ++i) {
    for (int j{0}; j < num_ans; ++j) {
      if (!soluble_evi[i][j].empty() && !insol_evi[i][j].empty()) {
        contradictions.push_back({static_cast<cat>(i), static_cast<an>(j)});
      }
    }
  }
}

//===-- main --===

int main() {
  std::deque<mix> mixes;
  gen_mix_list(mixes);

  evidence_table soluble_evi;
  gen_soluble_evi(mixes, soluble_evi);
  std::cout << "# rxns supporting solubility\n" << soluble_evi << "\n";

  evidence_table insol_evi;
  gen_insol_evi(mixes, soluble_evi, insol_evi);
  std::cout << "# rxns supporting insolubility\n" << insol_evi << "\n";

  std::deque<compound> contradictions;
  gen_contradictions(soluble_evi, insol_evi, contradictions);
  std::cout << "contradictions\n";
  for (const auto &contradiction : contradictions) {
    std::cout << "\n===-- " << contradiction
              << " --===\n"
                 "soluble evidence:"
              << soluble_evi[contradiction.first][contradiction.second]
              << "\n"
                 "insoluble evidence:"
              << insol_evi[contradiction.first][contradiction.second] << "\n";
  }
  std::cout << "\n";

  std::cout << "DONE\n";
}
