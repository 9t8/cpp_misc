#include <bits/stdc++.h>

using ll = long long;

int main()
{
  std::cin.tie(nullptr)->sync_with_stdio(false);

  double *dubPtr;
  double dubArray[100];

  dubPtr = new double[50];
  dubPtr = dubArray;
  dubPtr[75] = 9;
  delete[] dubPtr;
}
