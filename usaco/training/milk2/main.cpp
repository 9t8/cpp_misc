/*
ID: dragavo1
TASK: milk2
LANG: C++17
*/

#include <fstream>
#include <vector>

typedef long long ll;

int main() {
  std::ifstream fin("test.in");
  std::ofstream fout("test.out");

  std::vector<ll> itvls;  // begin, end, begin, end, ...

  ll N;
  fin >> N;
  for (ll i(0); i < N; ++i) {
    ll b, e;
    fin >> b >> e;
  }
}
