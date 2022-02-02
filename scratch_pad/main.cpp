#include <bits/stdc++.h>

using ll = long long;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::array<int, 0> a;
  try {
    std::cout << a.at(0) << '\n';
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}
