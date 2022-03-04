#include <bits/stdc++.h>

using ll = long long;

int main()
{
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll N, M;
  std::cin >> N >> M;

  std::vector<std::array<ll, 3>> cows(N);
  for (int i(0); i < N; ++i)
  {
    cows[i][0] = i;
    std::cin >> cows[i][1] >> cows[i][2];
  }
  sort(cows.begin(), cows.end());

  ll min_num_hungry(LLONG_MAX);
  std::vector<ll> best_path;

  do
  {
    std::unordered_set<ll> cereals;
    ll num_hungry(0);
    std::vector<ll> path(N);
    for (ll i(0); i < N; ++i)
    {
      path[i] = cows[i][0];
      if (cereals.count(cows[i][1]) == 0)
      {
        cereals.insert(cows[i][1]);
        break;
      }
      if (cereals.count(cows[i][2]) == 0)
      {
        cereals.insert(cows[i][2]);
        break;
      }
      ++num_hungry;
    }
    if (num_hungry < min_num_hungry)
    {
      min_num_hungry = num_hungry;
      best_path = path;
    }
  } while (next_permutation(cows.begin(), cows.end()));

  std::cout << min_num_hungry << '\n';
  for (const auto &num : best_path)
  {
    std::cout << num << '\n';
  }
}
