#include <iostream>
#include <set>
#include <vector>

typedef long long ll;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll N;
  std::cin >> N;

  std::vector<ll> locs(N);
  for (ll i(0); i < N; ++i) {
    ll h;
    std::cin >> h;
    locs[h - 1] = i;
  }

  std::set<ll> cows;
  ll ans(0);
  for (int i(N - 1); i >= 0; --i) {
    auto new_cow(cows.insert(locs[i]).first);

    if (new_cow != cows.begin())
      ans += *new_cow - *std::prev(new_cow) + 1;

    if (std::next(new_cow) != cows.end())
      ans += *std::next(new_cow) - *new_cow + 1;
  }
  std::cout << ans << "\n";
}
