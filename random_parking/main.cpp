#include <iostream>
#include <map>
#include <random>

int sim_rand_parking(const double &width) {
  // <area of valid itvls before this itvl, start of this itvl>
  std::map<double, double> valid_itvls{{0, 0}};

  int cars_parked(0);
  for (double area_valid_itvls(width - 1); area_valid_itvls >= 0;) {
    // area_valid_itvls := S(valid_pos?(x), 0, width)

    // insert new car
    static std::mt19937_64 rng;  // deterministic
    static std::uniform_real_distribution<> dist;

    double ar_valid_itvls_before(dist(
        rng,
        decltype(dist)::param_type(
            0,
#ifdef __clang__
            area_valid_itvls  // https://github.com/llvm/llvm-project/issues/19141
#else
            std::nextafter(area_valid_itvls, area_valid_itvls + 1)
#endif
            )));

    auto it_itvl(valid_itvls.lower_bound(ar_valid_itvls_before));
    double itvl_size(std::next(it_itvl) == valid_itvls.end()
                         ? area_valid_itvls - it_itvl->first
                         : std::next(it_itvl)->first - it_itvl->first);

    double left_space(it_itvl->second + ar_valid_itvls_before - it_itvl->first);

    double right_space(it_itvl->second + itvl_size - ar_valid_itvls_before);

    double lost_area(std::min(left_space, 1.) + std::min(right_space, 1.));

    // TODO? shorten/delete current itvl
    if (left_space >= 1) {
      // TODO: shorten current itvl
    }

    if (right_space >= 1) {
      // TODO: insert new itvl
    }

    area_valid_itvls = -1;
  }
  return cars_parked;
}

int main() { std::cout << sim_rand_parking(1) << "\n"; }
