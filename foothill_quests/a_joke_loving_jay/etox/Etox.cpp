#include <bits/stdc++.h>

using namespace std;

double etox_5_terms(double x)
{
  return 1 + x + x * x / 2. + x * x * x / 6. + x * x * x * x / 24.;
}

int main()
{
  cout << "Enter a value for x: ";

  string input;
  getline(cin, input);

  cout << etox_5_terms(stod(input)) << '\n';
}
