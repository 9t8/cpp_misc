

#pragma once

#include <bits/stdc++.h>

struct Trie {
  Trie() : _root(new Node()) {}

  ~Trie() { delete _root; }

  void insert(std::string s) { _root->insert(s); }

  bool lookup(std::string s) const { return _root->lookup(s); };

  size_t get_completions(std::string s, std::vector<std::string> &completions,
                         size_t limit) const {
    const Node *begin_node(traverse(s));
    if (begin_node != nullptr)
      return begin_node->get_completions(completions, limit);

    completions.clear();
    return 0;
  }

  std::string to_string(size_t limit) {
    std::string result("# Trie contents\n");

    std::vector<std::string> completions;
    get_completions("", completions, limit + 1);

    for (int i(0);
         i < static_cast<long long>(std::min(limit, completions.size())); ++i)
      result += completions[i] + '\n';

    if (completions.size() > limit)
      result += "...\n";

    return result;
  }

  size_t trie_sort(std::vector<std::string> &vec) const {
    return get_completions("", vec, -1);
  }

  struct Node {
    std::vector<Trie::Node *> next;

    ~Node() {
      for (const auto &el : next)
        delete el;
    }

    void insert(std::string s) {
      if (s[0] >= static_cast<long long>(next.size()))
        next.resize(s[0] + 1);

      if (next[s[0]] == nullptr)
        next[s[0]] = new Node();

      if (!s.empty())
        next[s[0]]->insert(s.substr(1));
    }

    const Node *traverse(std::string s) const {
      if (s.empty())
        return this;

      if (s[0] >= static_cast<long long>(next.size()) || next[s[0]] == nullptr)
        return nullptr;

      return next[s[0]]->traverse(s.substr(1));
    }

    bool lookup(std::string s) const {
      const Node *last_letter(traverse(s));
      return last_letter != nullptr && !last_letter->next.empty() &&
             last_letter->next[0] != nullptr;
    }

    size_t get_completions(std::vector<std::string> &completions,
                           size_t limit) const {
      completions.clear();
      if (limit == 0)
        return 0;

      struct Continuation {
        const Trie::Node *node;
        std::string partial;
      };

      std::queue<Continuation> unprocessed_nodes;
      unprocessed_nodes.push({this, ""});

      for (; !unprocessed_nodes.empty(); unprocessed_nodes.pop()) {
        Continuation cont = unprocessed_nodes.front();

        if (!cont.partial.empty() && cont.partial.back() == '\0') {
          cont.partial.pop_back();
          completions.push_back(cont.partial);

          if (completions.size() == limit)
            break;
        }

        for (char i(0); i < static_cast<long long>(cont.node->next.size()); ++i)
          if (cont.node->next[i] != nullptr)
            unprocessed_nodes.push({cont.node->next[i], cont.partial + i});
      }

      return completions.size();
    }

  } * _root;

  const Node *traverse(std::string s) const { return _root->traverse(s); }
};
