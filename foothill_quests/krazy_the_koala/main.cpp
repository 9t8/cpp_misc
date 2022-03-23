#include "Tree.h"

#include <bits/stdc++.h>

int main() {
  Tree t;
  t.make_special_config_1({"AABA", "ABAB", "ABBA", "BABA", "COBO",
                           "COCO", "CODO", "COFO", "COGO", "COHO",
                           "COJO", "COKO", "DIBI", "DIDI", "DIFI",
                           "DIGI", "DIHI", "DIJI", "DIKI", "DILI"});
  std::cout << t;
}
