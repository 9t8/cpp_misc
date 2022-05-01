#include <bits/stdc++.h>

class Datum {
public:
  virtual void eval() = 0;
};

class SimpleDatum : public Datum {
public:
  virtual void eval() {}
};

class List : public Datum {
public:
  virtual void eval() {}

private:
  std::vector<Datum *> elements;
};

int main() {
  // combine lexing and parsing?
  while (!std::cin.eof()) {
    std::cin >> std::ws;
    if (std::cin.peek() == '(') {
    }
  }
}
