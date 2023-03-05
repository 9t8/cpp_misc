#include <bits/stdc++.h>

typedef long long ll;

struct order {
  ll a, b, t;
};

int main() {  // friends are lines, go thru intersections of friends?
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll T;
  std::cin >> T;
  for (ll i(0); i < T; ++i) {
    ll N, tC, tM;
    std::cin >> N >> tC >> tM;
    std::vector<order> orders(N);
    for (order &o : orders) {
      std::cin >> o.a >> o.b >> o.t;
    }

    // mX = moonies spent on X
    const auto is_valid([&](ll mC, ll mM) {
      for (const order &o : orders) {
        if (o.a * (tC - mC) + o.b * (tM - mM) > o.t) {
          return false;
        }
      }
      return true;
    });

    ll min_m(tC - 1 + tM - 1);
    bool did_something(false);

    for (ll i(0); i < orders.size(); ++i) {
      double i_tC(static_cast<double>(orders[i].t - orders[i].b * tM) /
                  orders[i].a);
      double i_tM(static_cast<double>(orders[i].t - orders[i].a * tC) /
                  orders[i].b);
      double A(1 / i_tM), B(1 / i_tC), C(i_tC * i_tM);
      for (ll j(i + 1); j < orders.size(); ++j) {
        double j_tC(static_cast<double>(orders[j].t - orders[j].b * tM) /
                    orders[j].a);
        double j_tM(static_cast<double>(orders[j].t - orders[j].a * tC) /
                    orders[j].b);
        double D(1 / j_tM), E(1 / j_tC), F(j_tC * j_tM);
        double denom(E * A - B * D);
        if (denom == 0) {
          continue;
        }
        double x_tC((E * C - B * F) / denom);
        double x_tM((A * F - D * C) / denom);
        if (x_tC < 0 || x_tM < 0) {
          continue;
        }
        double x_mC(tC - x_tC), x_mM(tM - x_tM);
        ll m1(x_mC + std::ceil(x_mM));
        if (m1 < min_m && is_valid(x_mC, std::ceil(x_mM))) {
          min_m = m1;
          did_something = true;
          continue;
        }
        ll m2(std::ceil(x_mC) + x_mM);
        if (m2 < min_m && is_valid(std::ceil(x_mC), x_mM)) {
          min_m = m2;
          did_something = true;
          continue;
        }
        ll m3(std::ceil(x_mC) + std::ceil(x_mM));
        if (m3 < min_m && is_valid(std::ceil(x_mC), std::ceil(x_mM))) {
          min_m = m3;
          did_something = true;
          continue;
        }
      }
    }

    if (!did_something) {
      std::cerr << "did nothing\n";
      for (ll mC(0); mC < tC; ++mC) {
        for (ll mM(0); mM < tM; ++mM) {
          if (mC + mM < min_m && is_valid(mC, mM)) {
            min_m = mC + mM;
          }
        }
      }
    }

    std::cout << min_m << "\n";
  }
}
