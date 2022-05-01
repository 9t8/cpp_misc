#include <bits/stdc++.h>

using namespace std;

double eval_limerick(int dozen, int gross, int score) {
  return (dozen + gross + score + 3 * sqrt(4)) / 7 + 5 * 11;
}

int main(int argc, char **argv) {
  cout << eval_limerick(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])) << '\n';
}
