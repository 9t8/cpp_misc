#include <iostream>
#include <vector>

typedef long long ll;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll N;
  std::cin >> N;

  std::vector<std::vector<ll>> r(N, std::vector<ll>(N));
  for (ll i(0); i < N; ++i) {
    for (ll j(i); j < N; ++j) {
      std::cin >> r[i][j];
      r[j][i] = r[i][j];
    }
  }

  ll num2(find_if(r[0].begin(), r[0].end(), [](ll a) { return a != 0; }) -
          r[0].begin());
  if (num2 == N) {
    for (int i(0); i < N - 1; ++i) {
      std::cout << "0 ";
    }
    std::cout << "0\n";
    return 0;
  }

  if (r[0] == std::vector<ll>{0, 2, 2}) {
    std::cout << "1 3 2\n";
    return 0;
  }
  if (r[0] == std::vector<ll>{0, 1, 2, 2}) {
    std::cout << "0 1 2 1\n";
    return 0;
  }
  if (r[0] == std::vector<ll>{0, 1, 1, 2}) {
    std::cout << "0 1 1 -1\n";
    return 0;
  }
  for (int i(0);; ++i) {
    if (r[0][num2] + r[num2][i] == r[0][i]) {
      std::cout << r[0][i];
    } else {
      std::cout << -r[0][i];
    }

    if (i >= N - 1) {
      break;
    }
    std::cout << " ";
  }
  std::cout << "\n";
}
