#include <bits/stdc++.h>

#include "Trie.h"

class Tests {
 public:
  Trie *t;

  Trie::Node *traverse(std::string s) {
    Trie::Node *n = const_cast<Trie::Node *>(t->traverse(s));
    return n;
  }
  size_t get_completions(std::vector<std::string> &completions,
                         size_t limit) const {
    return t->_root->get_completions(completions, limit);
  }
  size_t get_completions(std::string s, std::vector<std::string> &completions,
                         size_t limit) const {
    return t->get_completions(s, completions, limit);
  }

  Trie::Node *getRoot() { return t->_root; }
};

int main() {
  std::string air = "air";
  std::string car = "car";
  std::string ca = "ca";
  std::string card = "card";
  std::string dart = "dart";
  Tests tests;
  // Yeah, I know, but it is convenient...
  Trie t;
  tests.t = &t;
  // What about the empty string?
  assert(tests.traverse("") == tests.getRoot());
  // First traverse should fail and therefore return null
  assert(tests.traverse(car) == nullptr);
  t.insert(car);
  // "air" is not in the trie, therefore return null
  assert(tests.traverse(air) == nullptr);
  // We never inserted "ca" even though car is in the trie.
  assert(tests.traverse(ca)->next[0] == nullptr);
  // we need to find car
  assert(tests.traverse(car)->next[0] != nullptr);
  // what about card?
  assert(tests.traverse(card) == nullptr);
  // Now go through the API
  assert(t.lookup(air) == false);
  assert(t.lookup(ca) == false);
  assert(t.lookup(car) == true);
  assert(t.lookup(card) == false);
  // Done with negative cases, let's insert more (tricky) strings
  t.insert(air);
  t.insert(ca);
  t.insert(card);
  // We have ca, car and card to lookup
  assert(t.lookup(air) == true);
  assert(t.lookup(ca) == true);
  assert(t.lookup(car) == true);
  assert(t.lookup(card) == true);

  // Add Junk to completion to make sure it is cleaned
  std::vector<std::string> completions{"a", "b"};
  // This will test the private API with limit 0
  assert(tests.get_completions(completions, 0) == 0);
  std::vector<std::string> expected{ca};
  assert(tests.get_completions(completions, 1) == 1);
  // Tests completion private API with one element
  assert(completions == expected);
  expected.push_back(air);
  expected.push_back(car);
  expected.push_back(card);
  assert(tests.get_completions(completions, 4) == 4);
  // Tests completion private API with 4 elements
  assert(completions == expected);
  // Tests completion Public API
  // Just like the provate one
  assert(tests.get_completions("", completions, 4) == 4);
  assert(completions == expected);
  // Test to_string
  std::cout << t.to_string(100) << "\n";
  // Test to_string with ellipses
  std::cout << t.to_string(2) << "\n";
  // Now test completions from a string onwards
  expected.clear();
  expected.shrink_to_fit();
  assert(tests.get_completions("zed", completions, 2) == 0);
  assert(completions == expected);
  assert(tests.get_completions("ca", completions, 2) == 2);
  expected.clear();
  expected.shrink_to_fit();
  expected.push_back("");
  expected.push_back("r");
  // The "strings" returned might not be really strings, it is anything
  // that ends in a null pointer
  assert(completions == expected);
}
