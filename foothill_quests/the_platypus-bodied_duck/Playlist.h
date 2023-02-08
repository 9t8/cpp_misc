#pragma once

#include <bits/stdc++.h>

class Playlist {
 public:
  class Song_Entry {
   public:
    Song_Entry(int id = 0, std::string name = "Unnamed")
        : _id(id), _name(name) {}

    int get_id() const { return _id; }

    std::string get_name() const { return _name; }

    bool set_id(int id) {
      if (id < 0) return false;

      _id = id;
      return true;
    }

    bool set_name(std::string name) {
      if (name.empty()) return false;

      _name = name;
      return true;
    }

    bool operator==(const Song_Entry &that) {
      return this->_id == that._id && this->_name == that._name;
    }

    bool operator!=(const Song_Entry &that) { return !(*this == that); }

    friend std::ostream &operator<<(std::ostream &os, const Song_Entry &s) {
      return os << "{ id: " << s.get_id() << ", name: " << s.get_name() << " }";
    }

   private:
    friend class Tests;

    int _id;
    std::string _name;
  };

  Playlist()
      : _head(new Node(Song_Entry(-1, "HEAD"))),
        _tail(_head),
        _prev_to_current(_head),
        _size(0) {}

  ~Playlist() { delete _head; }

  size_t get_size() const { return _size; }

  Song_Entry &get_current_song() const {
    if (_prev_to_current->get_next() == nullptr)
      return _head->get_song();
    else
      return _prev_to_current->get_next()->get_song();
  }

  Playlist *clear() {
    delete _head->get_next();
    _tail = _prev_to_current = _head = nullptr;
    _size = 0;

    return this;
  }

  Playlist *rewind() {
    _prev_to_current = _head;

    return this;
  }

  Playlist *push_back(const Song_Entry &s) {
    _tail = _tail->insert_next(new Node(s));

    ++_size;

    return this;
  }

  Playlist *push_front(const Song_Entry &s) {
    auto ptr_new(new Node(s));
    ptr_new->insert_next(_head->get_next());
    _head->insert_next(ptr_new);
    if (_tail == _head) _tail = ptr_new;

    ++_size;

    return this;
  }

  Playlist *insert_at_cursor(const Song_Entry &s) {
    auto ptr_new(new Node(s));
    ptr_new->insert_next(_prev_to_current->get_next());
    _prev_to_current->insert_next(ptr_new);
    if (_tail == _prev_to_current) _tail = ptr_new;

    ++_size;

    return this;
  }

  Playlist *remove_at_cursor() {
    if (_prev_to_current->get_next() == _tail) _tail = _prev_to_current;

    _prev_to_current->remove_next();

    --_size;

    return this;
  }

  Playlist *advance_cursor() {
    if (_prev_to_current == _tail) return nullptr;

    _prev_to_current = _prev_to_current->get_next();

    return this;
  }

  Playlist *circular_advance_cursor() {
    _prev_to_current = _prev_to_current->get_next();

    if (_prev_to_current == _tail) rewind();

    return this;
  }

  Song_Entry &find_by_id(int id) const {
    for (auto ptr_node(_head->get_next()); ptr_node != nullptr;
         ptr_node = ptr_node->get_next())
      if (ptr_node->get_song().get_id() == id) return ptr_node->get_song();

    return _head->get_song();
  }

  Song_Entry &find_by_name(std::string songName) const {
    for (auto ptr_node(_head->get_next()); ptr_node != nullptr;
         ptr_node = ptr_node->get_next())
      if (ptr_node->get_song().get_name() == songName)
        return ptr_node->get_song();

    return _head->get_song();
  }

  std::string to_string() const {
    std::ostringstream result;

    result << "Playlist: " << _size << " entries.\n";

    int i(0);
    for (auto ptr_node(_head->get_next()); ptr_node != nullptr;
         ptr_node = ptr_node->get_next()) {
      if (++i > 25) {
        result << "...\n";
        break;
      }

      result << ptr_node->get_song();
      if (ptr_node == _prev_to_current) result << " [P]";
      if (ptr_node == _tail) result << " [T]";
      result << "\n";
    }

    return result.str();
  }

 private:
  friend class Tests;

  class Node {
   public:
    Node(const Song_Entry &song = Song_Entry()) : _song(song), _next(nullptr) {}

    ~Node() {
      while (get_next() != nullptr) remove_next();
    }

    Song_Entry &get_song() { return _song; }

    Node *get_next() { return _next; }

    Node *insert_next(Node *p) { return _next = p; }

    Node *remove_next() {
      auto ptr_next_next(get_next()->get_next());
      get_next()->insert_next(nullptr);
      delete get_next();
      insert_next(ptr_next_next);

      return this;
    }

   private:
    friend class Tests;

    Song_Entry _song;
    Node *_next;
  };

  Node *_head, *_tail, *_prev_to_current;
  size_t _size;
};
