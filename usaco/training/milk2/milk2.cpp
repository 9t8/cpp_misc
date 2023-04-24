/*
ID: dragavo1
TASK: milk2
LANG: C++17
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
typedef long long ll;

int main() {
  // std::ifstream cin("milk2.in");
  // std::ofstream cout("milk2.out");

  size_t N;
  cin >> N;
  std::vector<std::pair<ll, ll>> itvls(N);
  for (auto &itvl : itvls) {
    cin >> itvl.first >> itvl.second;
  }
  std::sort(itvls.begin(), itvls.end());

  for (size_t i(itvls.size() - 1); i > 0; --i) {
    while (i < itvls.size() && itvls[i - 1].second >= itvls[i].first) {
      itvls[i - 1].first = std::min(itvls[i - 1].first, itvls[i].first);
      itvls[i - 1].second = std::max(itvls[i - 1].second, itvls[i].second);
      itvls.erase(itvls.begin() + static_cast<ll>(i));
    }
  }

  ll max_milking(0);
  for (const auto &itvl : itvls) {
    max_milking = std::max(max_milking, itvl.second - itvl.first);
  }
  cout << max_milking << " ";

  ll max_idle(0);
  for (size_t i(0); i + 1 < itvls.size(); ++i) {
    max_idle = std::max(max_idle, itvls[i + 1].first - itvls[i].second);
  }
  cout << max_idle << "\n";
}
