#include <iostream>

typedef long long ll;

constexpr bool any_factors(ll target, ll start, ll step) {
  if (start * start * 36 > target) {
    return false;
  }

  if (step == 1) {
    return target % (start * 6 + 1) == 0 || target % (start * 6 + 5) == 0;
  }

  return any_factors(target, start, step / 2) ||
         any_factors(target, start + step / 2, (step + 1) / 2);
}

constexpr bool is_prime(ll target) {
  return target == 2 || target == 3 || target == 5 ||
         (target > 1 && target % 2 != 0 && target % 3 != 0 && target % 5 != 0 &&
          !any_factors(target, 1, target / 6 + 1));
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::cout << is_prime(111111111111111111) << "\n";
}
