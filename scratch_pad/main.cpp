#include <bits/stdc++.h>

using ll = long long;

struct S {
  S() { std::cout << "S\n"; }
};

template <typename T> struct U {
  U() { std::cout << "U\n"; }
};

template <typename T> struct TS {
  static inline S s = S();

  static inline U<T> u = U<T>();

  TS() { std::cout << "TS\n"; };
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  TS<int> a;
  TS<double> b;
}
