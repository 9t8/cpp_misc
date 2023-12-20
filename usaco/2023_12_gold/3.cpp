#include <bits/stdc++.h>

typedef long long ll;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  // binary search
  // solution must be on barn

  ll N;
  std::cin >> N;

  std::vector<ll> x(N);
  for (ll &i : x) {
    std::cin >> i;
  }
  std::sort(x.begin(), x.end());

  std::vector<ll> dist_l(N);
  for (ll i(1); i < dist_l.size(); ++i) {
    dist_l[i] = dist_l[i - 1] + i * (x[i] - x[i - 1]);
  }

  std::vector<ll> dist_r(N);
  for (ll i(1); i < dist_r.size(); ++i) {
    ll j(dist_r.size() - 1 - i);
    dist_r[j] = dist_r[j + 1] + i * (x[j + 1] - x[j]);
  }

  dist_l.erase(std::unique(dist_l.begin(), dist_l.end()), dist_l.end());
  dist_r.erase(std::unique(dist_r.begin(), dist_r.end()), dist_r.end());

  ll Q;
  std::cin >> Q;
  for (ll i(0); i < Q; ++i) {
    ll a, b;
    std::cin >> a >> b;

    const auto waste([&](ll i) { return a * dist_l[i] + b * dist_r[i]; });

    const std::function<ll(ll, ll)> search([&](ll l, ll r) {
      if (l == r) {
        return waste(l);
      }

      ll mid((l + r) / 2);
      if ((waste(mid) < waste(mid + 1))) {
        return search(l, mid);
      } else {
        return search(mid + 1, r);
      }
    });

    std::cout << search(0, dist_l.size() - 1) << '\n';
  }
}
