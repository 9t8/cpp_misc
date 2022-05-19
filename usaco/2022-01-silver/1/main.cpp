#include <bits/stdc++.h>

using ll = long long;

ll solve(ll a, const ll &b) {
  std::deque<ll> path_to_b = {b};
  while (path_to_b.back() > 1)
    path_to_b.push_back(path_to_b.end()[-1] / 2);

  ll ops(0);
  while (a * 2 <= b) {
    auto next(*std::lower_bound(path_to_b.rbegin(), path_to_b.rend(), a));
    ops += next - a + 1;
    a = next * 2;
  }
  return b - a + ops;
}

ll search_solve(const ll &a, const ll &b) {
  ll dir_ops(solve(a, b));

  if (a == 1)
    return dir_ops;

  return std::min(dir_ops, 1 + a % 2 + search_solve((a + 1) / 2, b));
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll N;
  std::cin >> N;
  for (ll i(0); i < N; ++i) {
    ll p, q, ops(0);
    std::cin >> p >> q;

    while (p > q) {
      ops += 1 + p % 2;
      ++p /= 2;
    }

    std::cout << ops + search_solve(p, q) << "\n";
  }
}
