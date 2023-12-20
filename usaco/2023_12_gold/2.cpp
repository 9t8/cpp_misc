#include <bits/stdc++.h>

typedef long long ll;

struct road {
  ll dest, label;
};

struct trip {
  bool solved;
  ll len, label, sum;
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  // memoization

  ll N, M;
  std::cin >> N >> M;

  std::unordered_map<ll, std::vector<road>> roads;
  for (ll i(0); i < M; ++i) {
    ll a, b, l;
    std::cin >> a >> b >> l;
    roads[a].push_back(road{b, l});
  }
  for (auto &[k, e] : roads) {
    std::sort(e.begin(), e.end(),
              [](road a, road b) { return a.label < b.label; });
  }

  std::vector<trip> cache(N + 1);

  const std::function<trip(ll)> search([&](ll start) {
    if (cache[start].solved) {
      return cache[start];
    }

    const std::vector<road> &exits(roads[start]);
    for (const road &exit : exits) {
      trip exit_trip(search(exit.dest));

      if (exit_trip.len + 1 > cache[start].len ||
          (exit_trip.len + 1 == cache[start].len &&
           exit_trip.label < cache[start].label)) {
        cache[start].len = exit_trip.len + 1;
        cache[start].label = exit.label;
        cache[start].sum = exit_trip.sum + exit.label;
      }
    }
    cache[start].solved = true;
    return cache[start];
  });

  for (ll i(1); i <= N; ++i) {
    search(i);
    std::cout << cache[i].len << ' ' << cache[i].sum << '\n';
  }
}
