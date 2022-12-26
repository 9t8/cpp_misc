#include <iostream>
#include <vector>

typedef long long ll;

bool is_win(const ll &n) {
  // static std::unordered_map<ll, bool> cache;

  if (n <= 3) {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll T;
  std::cin >> T;
  for (ll i(0); i < T; ++i) {
    ll N;
    std::cin >> N;
    std::vector<ll> turns(N);
    for (ll j(0); j < N; ++j) {
      ll a;
      std::cin >> a;
      if (is_win(a)) {
        std::cout << "Farmer John\n";
        goto end;
      }
      if (is_win(a - 2)) {
        turns[j] = 2;
      }
      if (a % 4 == 0) {
        turns[j] = a / 4;
        if (turns[j] % 2) {
          ++turns[j];
        }
        continue;
      }
      turns[j] = a / 4 + 1;
      if (turns[j] % 2 == 0) {
        ++turns[j];
      }
    }
    {
      ll min_rounds(turns[0] / 2);
      bool john_wins(turns[0] % 2);
      for (int i(1); i < N; ++i) {
        ll rounds(turns[i] / 2);
        if (rounds < min_rounds) {
          min_rounds = rounds;
          john_wins = turns[i] % 2;
        }
      }
      if (john_wins) {
        std::cout << "Farmer John\n";
      } else {
        std::cout << "Farmer Nhoj\n";
      }
    }
  end:
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}
