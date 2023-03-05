#include <bits/stdc++.h>

typedef long long ll;
// (t, x, y)
typedef std::tuple<ll, ll, ll> grazing;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll G, N;
  std::cin >> G >> N;

  std::vector<grazing> grazings;
  for (ll i(0); i < G; ++i) {
    ll x, y, t;
    std::cin >> x >> y >> t;
    grazings.emplace_back(t, x, y);
  }
  std::sort(grazings.begin(), grazings.end());

  ll num_innocent(0);
  for (ll i(0); i < N; ++i) {
    ll x, y, t;
    std::cin >> x >> y >> t;

    const auto proves_innocence([&](const grazing &g) {
      ll dx(std::get<1>(g) - x);
      ll dy(std::get<2>(g) - y);
      ll dt(std::get<0>(g) - t);
      return dx * dx + dy * dy > dt * dt;
    });

    auto it_next(std::lower_bound(grazings.begin(), grazings.end(),
                                  grazing(t, -1e9, -1e9)));
    if ((it_next != grazings.begin() && proves_innocence(*(it_next - 1))) ||
        (it_next != grazings.end() && proves_innocence(*it_next))) {
      ++num_innocent;
    }
  }
  std::cout << num_innocent << "\n";
}
