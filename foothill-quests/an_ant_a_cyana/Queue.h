

#pragma once

#include <bits/stdc++.h>

template <typename T> class Queue {
public:
  static const int MAX_DISP_ELEMS = 100;

  static void set_sentinel(const T &elem) { _sentinel = elem; }

  static T get_sentinel() { return _sentinel; }

  Queue(size_t size) : _data(size + 1), _head(), _tail() {}

  bool is_empty() const { return size() == 0; }

  size_t size() const { return (_tail + _data.size() - _head) % _data.size(); }

  void resize(size_t s) {
    std::vector<T> new_data(s + 1);
    size_t new_tail(std::min(s, size()));

    for (auto &datum : new_data) {
      datum = peek();
      if (!dequeue())
        break;
    }

    _data = new_data;
    _head = 0;
    _tail = new_tail;
  }

  const T &peek() const { return is_empty() ? _sentinel : _data[_head]; }

  bool dequeue() {
    if (is_empty())
      return false;

    _head = (_head + 1) % _data.size();
    return true;
  }

  bool enqueue(const T &elem) {
    if (size() + 1 == _data.size())
      return false;

    _data[_tail] = elem;
    _tail = (_tail + 1) % _data.size();
    return true;
  }

  std::string to_string(size_t limit = MAX_DISP_ELEMS) const {
    std::ostringstream result;
    result << "# Queue - size = " << size() << "\ndata :";
    for (size_t i = _head; i != _tail; i = (i + 1) % _data.size()) {
      result << " " << _data[i];
    }
    result << "\n";

    return result.str();
  }

private:
  friend class Tests;

  static T _sentinel;

  std::vector<T> _data;
  size_t _head, _tail;
};

template <typename T> T Queue<T>::_sentinel = T();

template <typename T> void popalot(Queue<T> &q) {
  while (q.dequeue())
    ;
}
