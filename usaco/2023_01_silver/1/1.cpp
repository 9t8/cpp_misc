#include <iostream>
#include <unordered_map>

typedef long long ll;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ll t;
  std::cin >> t;
  for (ll i(0); i < t; ++i) {
    std::string in, out;
    std::cin >> in >> out;

    std::unordered_map<char, char> map;
    bool fail(false);
    for (size_t j(0); j < in.size(); ++j) {
      if (!map.count(in[j])) {
        map[in[j]] = out[j];
      }
      if (map[in[j]] != out[j]) {
        fail = true;
        break;
      }
    }

    if (fail) {
      std::cout << "-1\n";
      continue;
    }

    ll num_strokes(0);
    for (const auto &p : map) {
      if (p.first != p.second && p.second != 0) {
        ++num_strokes;
      }
    }

    // add number of cycles

    std::cout << num_strokes << "\n";
  }
}
