

#include "Pet.h"

#include <bits/stdc++.h>

using namespace std;

size_t Pet::_population(0);

string Pet::make_a_name(int len) {
  static const string vowels("aeiou"), consonants("bcdfghjklmnpqrstvwxyz");

  ostringstream name;
  bool starts_with_consonant(rand() % 2 == 0);
  for (int i(0); i < len; ++i) {
    if (i % 2 ^ starts_with_consonant) {
      name << consonants[rand() % consonants.size()];
    } else {
      name << vowels[rand() % vowels.size()];
    }
  }
  return name.str();
}

void Pet::get_n_pets(size_t n, std::vector<Pet> &pets, int name_len) {
  pets.resize(n);
  long prev_id = 0;
  for (size_t i = 0; i < n; i++) {
    long id = prev_id + 1 + rand() % 10;
    pets[i].set_id(id);
    pets[i].set_num_limbs(rand() % 9);
    pets[i].set_name(make_a_name(name_len));
    prev_id = id;
  }
}

Pet::Pet(string name, long id, int num_limbs)
    : _name(name), _id(id), _num_limbs(num_limbs) {
  ++Pet::_population;
}

Pet::~Pet() { --Pet::_population; }

string Pet::to_string() const {
  ostringstream result;
  result << "(Name: " << _name << ", ID: " << _id
         << ", Limb Count: " << _num_limbs << ")";
  return result.str();
}

string Pet::get_name() const { return _name; }

bool Pet::set_name(string name) {
  if (name.empty()) return false;

  _name = name;
  return true;
}

long Pet::get_id() const { return _id; }

bool Pet::set_id(long id) {
  if (id < 0) return false;

  _id = id;
  return true;
}

int Pet::get_num_limbs() const { return _num_limbs; }

bool Pet::set_num_limbs(int num_limbs) {
  if (num_limbs < 0) return false;

  _num_limbs = num_limbs;
  return true;
}

bool operator==(const Pet &pet1, const Pet &pet2) {
  return pet1.get_name() == pet2.get_name() && pet1.get_id() == pet2.get_id() &&
         pet1.get_num_limbs() == pet2.get_num_limbs();
}

bool operator!=(const Pet &pet1, const Pet &pet2) { return !(pet1 == pet2); }

ostream &operator<<(ostream &os, const Pet &pet) {
  return os << pet.to_string();
}
