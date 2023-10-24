// runs multiple random parking simulations at various lengths approximates
// renyi's parking constant at each length

#include <iomanip>
#include <iostream>
#include <random>

typedef long long ll;

double rand_num(const double ub) {
  static std::mt19937_64 rng(std::random_device{}());

  return std::uniform_real_distribution<>(0,
#ifdef __clang__ // https://github.com/llvm/llvm-project/issues/19141
                                          ub
#else
                                          std::nextafter(ub, ub + 1)
#endif
                                          )(rng);
}

ll rec(const double width) {
  if (width < 1) {
    return 0;
  }

  double x_new(rand_num(width - 1));
  return rec(x_new) + rec(width - (x_new + 1)) + 1;
}

ll it(const double width) {
  if (width < 1) {
    return 0;
  }

  ll n(0);

  // prefix sum of itvl lengths
  std::vector<double> itvl_prefixes{width - 1};

  for (; !itvl_prefixes.empty(); ++n) {
    double x_new(rand_num(itvl_prefixes.back()));

    // itvl containing new car
    auto itvl(lower_bound(itvl_prefixes.begin(), itvl_prefixes.end(), x_new));

    double left_offset(x_new - (itvl == itvl_prefixes.begin() ? 0 : itvl[-1])),
        right_offset(*itvl - x_new);

    // insert new car

    // remove interval
    if (left_offset < 1 && right_offset < 1) {
      double itvl_len(left_offset + right_offset);
      while (++itvl < itvl_prefixes.end()) {
        itvl[-1] = *itvl - itvl_len;
      }
      itvl_prefixes.pop_back();
      continue;
    }

    // add interval
    if (left_offset >= 1 && right_offset >= 1) {
      size_t stop(static_cast<size_t>(itvl - itvl_prefixes.begin()));
      itvl_prefixes.push_back(itvl_prefixes.back() - 2);
      for (size_t i(itvl_prefixes.size() - 2); i > stop; --i) {
        itvl_prefixes[i] = itvl_prefixes[i - 1] - 2;
      }
      itvl_prefixes[stop] = x_new - 1;
      continue;
    }

    // shorten interval
    double lost_area(std::min(left_offset, 1.) + std::min(right_offset, 1.));
    for (; itvl < itvl_prefixes.end(); ++itvl) {
      *itvl -= lost_area;
    }
  }

  return n;
}

int main() {
  std::cout << "   Width   Trials    μ_rec     μ_it" << std::endl;

  for (const double width :
       std::vector<double>{.9, 1, 2, 3, 3.5, 4, 5, 10, 1e3, 1e5}) {
    ll num_trials(static_cast<ll>(1e6 / width));

    ll rec_total(0);
    ll it_total(0);
    for (ll i(0); i < num_trials; ++i) {
      rec_total += rec(width);
      it_total += it(width);
    }

    std::cout << std::setw(8) << width << " " << std::setw(8) << num_trials
              << " " << std::setw(8)
              << static_cast<double>(rec_total) /
                     static_cast<double>(num_trials) / width
              << " " << std::setw(8)
              << static_cast<double>(it_total) /
                     static_cast<double>(num_trials) / width
              << std::endl;
  }
}
