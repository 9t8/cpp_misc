#include <bits/stdc++.h>

typedef long long ll;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll N;
  std::cin >> N;

  std::vector<std::string> rows(N - 1);
  for (std::string &row : rows) {
    std::cin >> row;
  }

  const auto col_prod([&](ll col, ll start, ll end) {
    for (ll i(start); i <= end; ++i) {
      if (rows[i][col] == '0') {
        return false;
      }
    }
    return true;
  });

  const auto execute([&](ll row, ll col) {
    bool sum(false);
    for (ll i(0); i <= col; ++i) {
      sum ^= col_prod(i, row, row + col - i);
    }
    return sum; // whether bridge exists
  });

  ll sum(0);
  for (ll row(0); row < rows.size(); ++row) {
    for (ll col(0); col < rows[row].size(); ++col) {
      if (execute(row, col)) {
        ++sum;
      }
    }
  }
  std::cout << sum << '\n';
}
