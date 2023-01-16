

#pragma once

#include <bits/stdc++.h>

class Stack_Int {
 public:
  size_t size() const { return _data.size(); }

  bool is_empty() const { return _data.empty(); }

  void push(int val) { _data.push_back(val); }

  int top(bool &success) const {
    if (is_empty()) {
      success = false;
      return 0;
    }
    success = true;
    return _data.back();
  }

  bool pop() {
    if (is_empty()) return false;

    _data.pop_back();
    return true;
  }

  bool pop(int &val) {
    bool temp;
    val = top(temp);
    return pop();
  }

  std::string to_string() const {
    std::ostringstream result;
    result << "Stack (" << size() << " elements):\n";
    for (int i(0); i < 10 && i < static_cast<int>(size()); ++i)
      result << _data.end()[-1 - i] << "\n";

    if (size() > 10) result << "...\n";

    result << "Elements, if listed above, are in increasing order of age.";
    return result.str();
  }

 private:
  friend class Tests;

  std::vector<int> _data;
};

class Stack_String {
 public:
  size_t size() const { return _data.size(); }

  bool is_empty() const { return _data.empty(); }

  void push(std::string val) { _data.push_back(val); }

  std::string top(bool &success) const {
    if (is_empty()) {
      success = false;
      return "";
    }
    success = true;
    return _data.back();
  }

  bool pop() {
    if (is_empty()) return false;

    _data.pop_back();
    return true;
  }

  bool pop(std::string &val) {
    bool temp;
    val = top(temp);
    return pop();
  }

  std::string to_string() const {
    std::ostringstream result;
    result << "Stack (" << size() << " elements):\n";
    for (int i(0); i < 10 && i < static_cast<int>(size()); ++i) {
      result << _data.end()[-1 - i] << "\n";
    }
    if (size() > 10) {
      result << "...\n";
    }
    result << "Elements, if listed above, are in increasing order of age.";
    return result.str();
  }

 private:
  friend class Tests;

  std::vector<std::string> _data;
};
