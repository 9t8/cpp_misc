#include <bits/stdc++.h>

typedef long long ll;
// (t_dep, arr city, t_arr)
typedef std::tuple<ll, ll, ll> flight_info;
typedef std::vector<std::vector<flight_info>> deps_type;

void rec(const deps_type &deps, const std::vector<ll> &a,
         std::vector<ll> &results, const ll city, const ll t_arr) {
  if (results[city] != -1 && results[city] <= t_arr) {
    return;
  }
  results[city] = t_arr;
  ll t_dep = t_arr + a[city];
  for (auto it_earliest_flight(std::lower_bound(
           deps[city].begin(), deps[city].end(), flight_info(t_dep, 0, 0)));
       it_earliest_flight != deps[city].end(); ++it_earliest_flight) {
    // maybe update results here first for performance
    rec(deps, a, results, std::get<1>(*it_earliest_flight),
        std::get<2>(*it_earliest_flight));
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll N, M;
  std::cin >> N >> M;

  deps_type deps(N);
  for (ll i(0); i < M; ++i) {
    ll c, r, d, s;
    std::cin >> c >> r >> d >> s;
    --c;
    --d;
    // remove flights to origin
    if (d != 0) {
      deps[c].emplace_back(r, d, s);
    }
  }
  for (auto &city : deps) {
    std::sort(city.begin(), city.end());
  }

  std::vector<ll> a(N);
  for (ll &e : a) {
    std::cin >> e;
  }

  std::vector<ll> results(N, -1);
  results[0] = 0;
  for (const flight_info &flight : deps[0]) {
    rec(deps, a, results, std::get<1>(flight), std::get<2>(flight));
  }
  for (const ll result : results) {
    std::cout << result << "\n";
  }
}
