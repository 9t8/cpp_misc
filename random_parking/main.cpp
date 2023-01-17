#include <iostream>
#include <map>
#include <random>

int sim_rand_parking(const double &width) {
  // <area of valid itvls before this itvl, start of this itvl>
  std::map<double, double> valid_itvls{{0, 0}};

  int cars_parked(0);
  // valid_area <- S_{0}^{width} valid_pos?(x)
  for (double valid_area(width - 1); valid_area >= 0;) {
    static std::mt19937_64 rng;  // deterministic
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

    // insert new car
    auto it_itvl(valid_itvls.lower_bound(area_before_new_car));
    double itvl_size(std::next(it_itvl) == valid_itvls.end()
                         ? valid_area - it_itvl->first
                         : std::next(it_itvl)->first - it_itvl->first);

    double left_space(it_itvl->second + area_before_new_car - it_itvl->first);

    double right_space(it_itvl->second + itvl_size - area_before_new_car);

    double lost_area(std::min(left_space, 1.) + std::min(right_space, 1.));

    // TODO? shorten/delete current itvl
    if (left_space >= 1) {
      // TODO: shorten current itvl
    }

    if (right_space >= 1) {
      // TODO: insert new itvl
    }

    valid_area = -1;
  }
  return cars_parked;
}

int main() { std::cout << sim_rand_parking(1) << "\n"; }
