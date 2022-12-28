#include <iostream>

typedef long long ll;

int main(int argc, const char *[]) {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int k(0x7fffffff);
  k += argc;

  std::cout << k << "\n";
}
