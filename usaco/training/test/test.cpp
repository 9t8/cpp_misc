/*
ID: dragavo1
TASK: test
LANG: C++17
*/

#include <fstream>

typedef long long ll;

int main() {
  std::ofstream fout("test.out");
  std::ifstream fin("test.in");

  ll a, b;
  fin >> a >> b;
  fout << a + b << "\n";
}
