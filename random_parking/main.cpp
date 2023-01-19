#include <cassert>
#include <iostream>
#include <random>

int sim_rand_parking(const double &width) {
  int cars_parked(0);

  // prefix sum of preceding valid area for each itvl
  std::vector<double> itvl_prefixes({0});

  // valid_area = S_{0}^{width} valid_pos?(x)
  for (double valid_area(width - 1); valid_area >= 0; ++cars_parked) {
    // generate random location for new car
    static std::mt19937_64 rng;  // currently deterministic
    static std::uniform_real_distribution<> dist;
    double area_before_new_car(dist(
        rng,
#ifdef __clang__
        // https://github.com/llvm/llvm-project/issues/19141
        decltype(dist)::param_type(0, valid_area)
#else
        decltype(dist)::param_type(0,
                                   std::nextafter(valid_area, valid_area + 1))
#endif
            ));

    auto selected_itvl(lower_bound(itvl_prefixes.begin(), itvl_prefixes.end(),
                                   area_before_new_car));

    double itvl_end(selected_itvl + 1 == itvl_prefixes.end()
                        ? valid_area
                        : selected_itvl[1]),
        left_offset(area_before_new_car - *selected_itvl),
        right_offset(itvl_end - area_before_new_car);
    assert(left_offset >= 0);  // asserts not working
    assert(right_offset >= 0);

    // insert new car
    if (left_offset < 1 && right_offset < 1) {
      // remove interval
      double itvl_len(itvl_end - *selected_itvl);
      while (++selected_itvl < itvl_prefixes.end()) {
        selected_itvl[-1] = *selected_itvl - itvl_len;
      }
      itvl_prefixes.pop_back();
      valid_area -= itvl_len;
      continue;
    }
    if (left_offset >= 1 && right_offset >= 1) {
      // add new interval
      size_t stop(static_cast<size_t>(selected_itvl - itvl_prefixes.begin()) +
                  1);
      valid_area -= 2;
      itvl_prefixes.push_back(itvl_prefixes.back() - 2);
      for (size_t i(itvl_prefixes.size() - 2); i > stop; --i) {
        itvl_prefixes[i] = itvl_prefixes[i - 1] - 2;
      }
      itvl_prefixes[stop] = area_before_new_car - 1;
      continue;
    }
    // move/shorten interval
    double lost_area(std::min(left_offset, 1.) + std::min(right_offset, 1.));
    while (++selected_itvl < itvl_prefixes.end()) {
      *selected_itvl -= lost_area;
    }
    valid_area -= lost_area;
  }
  return cars_parked;
}

int main() { std::cout << sim_rand_parking(1) << "\n"; }
