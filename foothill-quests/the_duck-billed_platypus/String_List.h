

#pragma once

#include <bits/stdc++.h>

// Important implementation note: With the exception of to_string(), find(), and
// clear(), all list methods below should operate in a constant amount of time
// regardless of the size of the String_List instance.

// The semantics of _prev_to_current is such that it always points to the node
// *BEFORE* the current one. This makes the manipulations easy because we can
// only look forward (and not back) in singly linked lists.

class String_List {
public:
  String_List()
      : _head(new Node("_SENTINEL_")), _tail(_head), _prev_to_current(_head),
        _size(0) {}

  ~String_List() {
    clear();
    delete _head;
  }

  String_List *insert_at_current(std::string s) {
    auto ptr_new(new Node(s));
    ptr_new->next = _prev_to_current->next;
    _prev_to_current->next = ptr_new;
    if (_tail == _prev_to_current)
      _tail = ptr_new;

    ++_size;

    return this;
  }

  String_List *push_back(std::string s) {
    _tail = _tail->next = new Node(s);

    ++_size;

    return this;
  }

  String_List *push_front(std::string s) {
    auto ptr_new(new Node(s));
    ptr_new->next = _head->next;
    _head->next = ptr_new;
    if (_tail == _head)
      _tail = ptr_new;

    ++_size;

    return this;
  }

  String_List *advance_current() {
    if (_prev_to_current == _tail)
      return nullptr;

    _prev_to_current = _prev_to_current->next;

    return this;
  }

  std::string get_current() const { return _prev_to_current->next->data; }

  String_List *remove_at_current() {
    if (_prev_to_current->next == _tail)
      _tail = _prev_to_current;

    auto ptr_next(_prev_to_current->next->next);
    delete _prev_to_current->next;
    _prev_to_current->next = ptr_next;

    --_size;

    return this;
  }

  size_t get_size() const { return _size; }

  String_List *rewind() {
    _prev_to_current = _head;

    return this;
  }

  void clear() {
    while (_head->next != nullptr) {
      auto ptr_curr_node(_head->next);
      _head->next = ptr_curr_node->next;
      delete ptr_curr_node;
    }

    _tail = _prev_to_current = _head;
    _size = 0;
  }

  // Find a specific item. Does NOT change cursor.

  // The following returns a reference to the target string if found. But what
  // will you do if you didn't find the requested string? Using sentinel markers
  // is one way to handle that situation. Usually there's only one copy of the
  // sentinel that's global. We will use a local one so it's cleaner with a
  // little more risk (what's the risk?)

  std::string &find_item(std::string s) const {
    for (auto ptr_node(_head->next); ptr_node != nullptr;
         ptr_node = ptr_node->next)
      if (ptr_node->data == s)
        return ptr_node->data;

    static std::string sentinel;
    return sentinel = _head->data;
  }

  // Print up to max_lines lines starting at _prev_to_current->next. If the
  // caller wants to print from the beginning of the list, they should rewind()
  // it first.

  std::string to_string() const {
    std::ostringstream result;

    result << "# String_List - " << get_size()
           << " entries total. Starting at cursor:\n";

    int i(0);
    for (auto ptr_node(_prev_to_current->next); ptr_node != nullptr;
         ptr_node = ptr_node->next) {
      if (++i >= 25) {
        result << "...\n";
        break;
      }
      result << ptr_node->data << '\n';
    }

    return result.str();
  }

private:
  friend class Tests;

  struct Node {
    std::string data;
    Node *next;
    Node(std::string s = "") : data(s), next(nullptr) {}
  };

  Node *_head, *_tail, *_prev_to_current;
  size_t _size;
};
