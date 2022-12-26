#include <iostream>
#include <unordered_set>
#include <vector>

typedef long long ll;

struct order {
  ll src, dest, amt;
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll N;
  std::cin >> N;

  std::vector<ll> h(N);
  ll bales_needed(0);
  for (ll i(0); i < N; ++i) {
    std::cin >> h[i];
    bales_needed += h[i];
  }
  bales_needed /= N;

  std::vector<std::unordered_set<ll>> roads(N);
  for (ll i(0); i < N - 1; ++i) {
    ll a, b;
    std::cin >> a >> b;
    --a;
    --b;
    roads[a].insert(b);
    roads[b].insert(a);
  }

  std::vector<order> pushes, pulls;

  ll barns_cleared(0);
  while (barns_cleared < N - 1) {
    for (ll i(0); i < N; ++i) {
      if (roads[i].size() == 1) {
        if (h[i] > bales_needed) {
          pushes.push_back({i, *roads[i].begin(), h[i] - bales_needed});
        } else if (h[i] < bales_needed) {
          pulls.push_back({*roads[i].begin(), i, bales_needed - h[i]});
        }
        h[*roads[i].begin()] += h[i] - bales_needed;
        h[i] = bales_needed;

        roads[*roads[i].begin()].erase(i);
        ll new_i(*roads[i].begin());
        roads[i].clear();
        i = new_i - 1;

        ++barns_cleared;
      }
    }
  }

  std::cout << pushes.size() + pulls.size() << "\n";
  for (ll i(0); i < (ll)pushes.size(); ++i) {
    std::cout << pushes[i].src + 1 << " " << pushes[i].dest + 1 << " "
              << pushes[i].amt << "\n";
  }
  for (ll i((ll)pulls.size() - 1); i >= 0; --i) {
    std::cout << pulls[i].src + 1 << " " << pulls[i].dest + 1 << " "
              << pulls[i].amt << "\n";
  }
}
