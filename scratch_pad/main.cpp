#include <iostream>

using ll = long long;

template <typename t, size_t sz>
t &last(t (&super_duper_long_variable_name_for_an_array)[sz]) {
  return super_duper_long_variable_name_for_an_array[sz - 1];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int arr[]{0, 1, 2, 3};
  std::cout << last(arr) << "\n";
}
