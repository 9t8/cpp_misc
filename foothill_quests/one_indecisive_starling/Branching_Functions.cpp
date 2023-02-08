#include <bits/stdc++.h>

using namespace std;

double mean_of_3(int n1, int n2, int n3) { return (n1 + n2 + n3) / 3.; }

int max_of_5(int n1, int n2, int n3, int n4, int n5) {
  return max({n1, n2, n3, n4, n5});
}

int min_of_5(int n1, int n2, int n3, int n4, int n5) {
  return min({n1, n2, n3, n4, n5});
}

bool sides_make_triangle(int a, int b, int c) {
  int p(a + b + c);
  return a * 2 < p && b * 2 < p && c * 2 < p;
}

bool angles_make_triangle(int A, int B, int C) { return A + B + C == 180; }

bool is_a_leap_year(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
