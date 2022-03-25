#include <bits/stdc++.h>

using ll = long long;

struct s {
  virtual ~s() {}

  virtual void f() { std::cout << "s\n"; }
};

struct t : public s {
  virtual ~t() {}

  void f() { std::cout << "t\n"; }
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  s *p(new t);
  p->f();
  static_cast<s>(*p).f();
  delete p;
}
