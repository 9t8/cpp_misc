#include "Pet_Store.h"

#include <bits/stdc++.h>

using namespace std;

Pet_Store::Pet_Store(size_t n) : _pets(n), _sort_order(NONE) {}

void Pet_Store::set_size(size_t n) { _pets.resize(n); }

size_t Pet_Store::get_size() const { return _pets.size(); }

void Pet_Store::clear() { _pets.clear(); }

void Pet_Store::populate_with_n_random_pets(size_t n)
{
  Pet::get_n_pets(n, _pets, 7);
  _sort_order = BY_ID;
}

// These two functions can be conveniently made anonymous "lambda" functions
// defined within the scope of the functions where they're used (but only
// c++-11 on. For now we're just going to leave them here. It's straightforward
// to move them in. Just look up c++ lambda functions if you want. If you want
// to know but don't understand it, I'm happy to explain what they are. Ask me
// in the forums. It's not necessary to know about it to ace this course.
//
// You are free to experiment by hacking the functions below, but restore their
// correct functionalities before submitting your lab.
//

bool Pet_Store::_id_compare(const Pet &p1, const Pet &p2)
{
  return p1.get_id() < p2.get_id();
}

bool Pet_Store::_name_compare(const Pet &p1, const Pet &p2)
{
  return p1.get_name() < p2.get_name();
}

void Pet_Store::_sort_pets_by_id()
{
  std::sort(_pets.begin(), _pets.end(), Pet_Store::_id_compare);
  _sort_order = BY_ID;
}

void Pet_Store::_sort_pets_by_name()
{
  std::sort(_pets.begin(), _pets.end(), Pet_Store::_name_compare);
  _sort_order = BY_NAME;
}

bool Pet_Store::find_pet_by_id_lin(long id, Pet &pet)
{
  for (auto it(_pets.begin()); it != _pets.end(); ++it)
  {
    if (it->get_id() == id)
    {
      pet = *it;
      return true;
    }
  }
  return false;
}

bool Pet_Store::find_pet_by_name_lin(string name, Pet &pet)
{
  for (auto it(_pets.begin()); it != _pets.end(); ++it)
  {
    if (it->get_name() == name)
    {
      pet = *it;
      return true;
    }
  }
  return false;
}

// When this method starts, the _pets[] vector must be sorted in
// non-descending order by _id. If it is not already, then it will be
// resorted.
bool Pet_Store::find_pet_by_id_bin(long id, Pet &pet)
{
  if (_sort_order != BY_ID)
    _sort_pets_by_id();

  for (int first(0), last(_pets.size()); first < last;)
  {
    int mid((first + last) / 2);
    if (_pets[mid].get_id() == id)
    {
      pet = _pets[mid];
      return true;
    }
    if (_pets[mid].get_id() > id)
    {
      last = mid;
    }
    else
    {
      first = mid + 1;
    }
  }
  return false;
}

// When this method is called, the _pets[] vector must be sorted in
// lexicographic non-descending order by _name. If it is not already,
// then it will be resorted.
bool Pet_Store::find_pet_by_name_bin(string name, Pet &pet)
{
  if (_sort_order != BY_NAME)
    _sort_pets_by_name();

  for (int first(0), last(_pets.size()); first < last;)
  {
    int mid((first + last) / 2);
    if (_pets[mid].get_name() == name)
    {
      pet = _pets[mid];
      return true;
    }
    if (_pets[mid].get_name() > name)
    {
      last = mid;
    }
    else
    {
      first = mid + 1;
    }
  }
  return false;
}

// Return a string representation of the pets with indexes n1 through n2
// inclusive, exclusive of non-existent indices
// Each pet is on a line by itself.
string Pet_Store::to_string(size_t n1, size_t n2)
{
  string result;
  for (auto i(n1); i < n2; ++i)
  {
    result.append(_pets[i].to_string()).append("\n");
  }
  return result;
}
