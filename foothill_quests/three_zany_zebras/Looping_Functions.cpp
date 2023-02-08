#include "Looping_Functions.h"

#include <bits/stdc++.h>

using namespace std;

bool play_game(int n) {
  cout << "Welcome to my number guessing game\n\n";

  for (int i(1); i <= 6; ++i) {
    cout << "Enter your guess: ";
    int guess;
    cin >> guess;
    cout << "\nYou entered: " << guess << "\n";

    if (guess == n) {
      cout << "You found it in " << i << " guess(es).\n";
      return true;
    }
  }

  cout << "I'm sorry. You didn't find my number.\nIt was " << n << "\n";
  return false;
}

double etox(double x, size_t n) {
  double ans(0);
  for (int i(0); i < static_cast<int>(n); ++i) {
    ans += pow(x, i) / tgamma(i + 1);
  }
  return ans;
}

size_t count_chars(string s, char c) { return count(s.begin(), s.end(), c); }

size_t gcd(size_t n1, size_t n2) {
  while (n2 != 0) {
    n1 %= n2;
    swap(n1, n2);
  }
  return n1;
}

string get_ap_terms(int a, int d, size_t n) {
  if (n == 0) return "";

  ostringstream result;
  result << a;
  for (int i(1); i < static_cast<int>(n); ++i) {
    result << "," << a + d * i;
  }
  return result.str();
}

string get_gp_terms(double a, double r, size_t n) {
  if (n == 0) return "";

  ostringstream result;
  result << a;
  for (int i(1); i < static_cast<int>(n); ++i) {
    result << "," << a * pow(r, i);
  }
  return result.str();
}

double get_nth_fibonacci_number(size_t n) {
  double a(0), b(1);
  for (int i(0); i < static_cast<int>(n); ++i) {
    swap(a, b);
    a += b;
  }
  return a;
}
