

#pragma once

#include <bits/stdc++.h>

class Tree {
public:
  Tree();

  ~Tree();

  Tree(const Tree &that) { *this = that; }

  Tree &operator=(const Tree &that); // Deep clone

  std::string to_string() const;

  void make_special_config_1(const std::vector<std::string> &names);

  bool operator==(const Tree &that) const {
    // TODO
  }

  bool operator!=(const Tree &that) const {
    // TODO
  }

  friend std::ostream &operator<<(std::ostream &os, const Tree &tree) {
    // TODO
  }

private:
  friend class Tests;

  struct Node {
    std::string _data;
    Node *_sibling, *_child;

    static bool is_equal(const Node *p1, const Node *p2);

    Node(std::string s = "") : _data(s), _sibling(nullptr), _child(nullptr) {}

    Node(const Node &that) { *this = that; }

    const Node &operator=(const Node &that) {
      _data = that.get_data();
      if (that._sibling == nullptr) {
        delete _sibling;
      } else {
        if (_sibling == nullptr)
          _sibling = new Node();
        *_sibling = *that._sibling;
      }
      if (that._child == nullptr) {
        delete _child;
      } else {
        if (_child == nullptr)
          _child = new Node();
        *_child = *that._child;
      }
      return *this;
    }

    ~Node();

    std::string get_data() const { return _data; }

    void set_data(std::string s) { _data = s; }

    Node *insert_sibling(Node *p) {
      Node *last_node = this;
      while (last_node->_sibling != nullptr)
        last_node = last_node->_sibling;
      return last_node->_sibling = p;
    }

    Node *insert_child(Node *p) {
      return (_child == nullptr ? this : insert_sibling(new Node()))->_child =
                 p;
    }

    std::string to_string() const;

    bool operator==(const Node &that) const;

    bool operator!=(const Node &that) const;
  };
  Node *_root;
};
