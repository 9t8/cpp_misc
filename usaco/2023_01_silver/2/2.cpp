#include <bits/stdc++.h>

typedef long long ll;

// The second and third flips switch the same sign back and forth.

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll n;
  std::cin >> n;
  std::vector<std::string> dirs(n);
  std::vector<ll> right_prices(n), bottom_prices(n);
  for (ll i(0); i < n; ++i) {
    std::cin >> dirs[i] >> right_prices[i];
  }
  for (ll i(0); i < n; ++i) {
    std::cin >> bottom_prices[i];
  }
  
  // [n][n] stores total cost
  std::vector<std::vector<ll>> cow_counts(n + 1, std::vector<ll>(n + 1, 1));
  for (ll row(0); row < n + 1; ++row) {
    for (ll col(0); col < n + 1; ++col) {
      if (row == n || col == n) {
        cow_counts[row][col] = 0;
      }
      if (col > 0 && row < n && dirs[row][col - 1] == 'R') {
        cow_counts[row][col] += cow_counts[row][col - 1];
      }
      if (row > 0 && col < n && dirs[row - 1][col] == 'D') {
        cow_counts[row][col] += cow_counts[row - 1][col];
      }
    }
  }
  for (ll row(0); row < n; ++row) {
    cow_counts[n][n] += cow_counts[row][n] * right_prices[row];
  }
  for (ll col(0); col < n; ++col) {
    cow_counts[n][n] += cow_counts[n][col] * bottom_prices[col];
  }
  std::cout << cow_counts[n][n] << "\n";

  ll q;
  std::cin >> q;
  for (ll i(0); i < q; ++i) {
    ll flip_row, flip_col;
    std::cin >> flip_row >> flip_col;
    --flip_row;
    --flip_col;

    const auto follow([&](ll row, ll col, bool remove) -> ll {
      ll change(cow_counts[row][col] * (remove ? -1 : 1));
      for (;;) {
        if (dirs[row][col] == 'R') {
          ++col;
        } else {
          ++row;
        }
        cow_counts[row][col] += change;
        if (col == n) {
          return change * right_prices[row];
        }
        if (row == n) {
          return change * bottom_prices[col];
        }
      }
    });

    cow_counts[n][n] += follow(flip_row, flip_col, true);
    dirs[flip_row][flip_col] = dirs[flip_row][flip_col] == 'R' ? 'D' : 'R';
    cow_counts[n][n] += follow(flip_row, flip_col, false);

    std::cout << cow_counts[n][n] << "\n";
  }
}
