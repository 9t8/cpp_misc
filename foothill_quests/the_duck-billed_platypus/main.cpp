#include "String_List.h"

#include <bits/stdc++.h>

using namespace std;

int main() {
  String_List sl;
  sl.push_back("a");
  sl.push_back("s");
  sl.push_front("f");
  sl.advance_current();
  sl.remove_at_current();
}
