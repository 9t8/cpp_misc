#include <bits/stdc++.h>

using ll = long long;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll a(1), b(2);
  a ^= b ^= a ^= b;
  std::cout << a << b << '\n';
}
