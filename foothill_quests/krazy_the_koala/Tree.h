

#pragma once

#include <bits/stdc++.h>

class Tree
{
public:
  Tree() : _root(new Node("ROOT")) {}

  Tree(const Tree &that) : _root(new Node()) { *this = that; }

  ~Tree() { delete _root; }

  Tree &operator=(const Tree &that)
  {
    *_root = *that._root;
    return *this;
  }

  std::string to_string() const
  {
    return "# Tree rooted at " + _root->_data +
           "\n# The following lines are of the form:\n"
           "#   node: child1 child2...\n" +
           _root->to_string() + "# End of Tree\n";
  }

  void make_special_config_1(const std::vector<std::string> &names)
  {
    _root = new Node("ROOT");
    _root->insert_sibling(new Node(names[0]))
        ->insert_sibling(new Node(names[1]))
        ->insert_sibling(new Node(names[2]))
        ->insert_sibling(new Node(names[3]));
    _root->_sibling->insert_child(new Node(names[4]))
        ->insert_sibling(new Node(names[5]));
    _root->_sibling->_sibling->insert_child(new Node(names[6]))
        ->insert_sibling(new Node(names[7]));
    _root->_sibling->_sibling->_sibling->insert_child(new Node(names[8]))
        ->insert_sibling(new Node(names[9]));
    _root->_sibling->_sibling->_sibling->_sibling
        ->insert_child(new Node(names[10]))
        ->insert_sibling(new Node(names[11]));
    _root->_sibling->_child->insert_child(new Node(names[12]));
    _root->_sibling->_child->_sibling->insert_child(new Node(names[13]));
    _root->_sibling->_sibling->_child->insert_child(new Node(names[14]));
    _root->_sibling->_sibling->_child->_sibling->insert_child(
        new Node(names[15]));
    _root->_sibling->_sibling->_sibling->_child->insert_child(
        new Node(names[16]));
    _root->_sibling->_sibling->_sibling->_child->_sibling->insert_child(
        new Node(names[17]));
    _root->_sibling->_sibling->_sibling->_sibling->_child->insert_child(
        new Node(names[18]));
    _root->_sibling->_sibling->_sibling->_sibling->_child->_sibling
        ->insert_child(new Node(names[19]));
  }

  bool operator==(const Tree &that) const { return *_root == *that._root; }

  bool operator!=(const Tree &that) const { return !(*this == that); }

  friend std::ostream &operator<<(std::ostream &os, const Tree &tree)
  {
    return os << tree.to_string();
  }

private:
  friend class Tests;

  struct Node
  {
    std::string _data;
    Node *_sibling, *_child;

    static bool is_equal(const Node *p1, const Node *p2)
    {
      if (p1 == nullptr || p2 == nullptr)
        return p1 == nullptr && p2 == nullptr;

      return p1 == p2 ||
             (p1->_data == p2->_data && is_equal(p1->_sibling, p2->_sibling) &&
              is_equal(p1->_child, p2->_child));
    }

    Node(std::string s = "") : _data(s), _sibling(nullptr), _child(nullptr) {}

    Node(const Node &that) : _sibling(nullptr), _child(nullptr)
    {
      *this = that;
    }

    const Node &operator=(const Node &that)
    {
      _data = that._data;
      if (that._sibling == nullptr)
      {
        delete _sibling;
        _sibling = nullptr;
      }
      else
      {
        if (_sibling == nullptr)
          _sibling = new Node();
        *_sibling = *that._sibling;
      }
      if (that._child == nullptr)
      {
        delete _child;
        _child = nullptr;
      }
      else
      {
        if (_child == nullptr)
          _child = new Node();
        *_child = *that._child;
      }
      return *this;
    }

    ~Node()
    {
      delete _sibling;
      delete _child;
    }

    std::string get_data() const { return _data; }

    void set_data(std::string s) { _data = s; }

    Node *insert_sibling(Node *p)
    {
      Node *last_node = this;
      while (last_node->_sibling != nullptr)
        last_node = last_node->_sibling;
      return last_node->_sibling = p;
    }

    Node *insert_child(Node *p)
    {
      if (_child == nullptr)
        return _child = p;

      return _child->insert_sibling(p);
    }

    std::string to_string() const
    {
      std::string result(_data + " :");
      for (auto p_it(_child); p_it != nullptr; p_it = p_it->_sibling)
      {
        result += " " + p_it->_data;
      }
      result += '\n';

      if (_child == nullptr)
        return result;

      result += "# Child of " + _data + "\n" + _child->to_string();
      for (auto p_it(_child); p_it->_sibling != nullptr;
           p_it = p_it->_sibling)
      {
        result +=
            "# Next sib of " + p_it->_data + "\n" + p_it->_sibling->to_string();
      }
      return result;
    }

    bool operator==(const Node &that) const { return is_equal(this, &that); }

    bool operator!=(const Node &that) const { return !(*this == that); }
  };

  Node *_root;
};
