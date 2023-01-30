#include <bits/stdc++.h>

typedef long long ll;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll n;
  std::cin >> n;
  
  std::vector<ll> a(n);
  ll num_moves(0);
  for (auto &e : a) {
    std::cin >> e;
    num_moves += e;
  }

  size_t loc(0);
  bool going_right(true);
  for (ll i(0); i < num_moves; ++i) {
    const auto move([&](bool go_right) -> void {
      if (going_right = go_right) {
        --a[loc];
        ++loc;
        std::cout << "R";
      } else {
        --loc;
        --a[loc];
        std::cout << "L";
      }
    });

    if (loc == 0) {
      move(true);
      continue;
    }
    if (loc == a.size()) {
      move(false);
      continue;
    }
    if (going_right) {
      move(a[loc] > 0);
    } else {
      move(a[loc - 1] == 1 && a[loc] > 0);
    }
  }
  std::cout << "\n";
}
