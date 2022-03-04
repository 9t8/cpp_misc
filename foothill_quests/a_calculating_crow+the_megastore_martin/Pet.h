#pragma once

#include <bits/stdc++.h>

class Pet
{
public:
  static std::string make_a_name(int len);

  static void get_n_pets(size_t n, std::vector<Pet> &pets, int name_length);

  static size_t get_population() { return _population; }

  Pet(std::string name = "", long id = -1, int num_limbs = 0);

  ~Pet();

  std::string to_string() const;

  std::string get_name() const;

  bool set_name(std::string name);

  long get_id() const;

  bool set_id(long id);

  int get_num_limbs() const;

  bool set_num_limbs(int num_limbs);

private:
  friend class Tests;

  static size_t _population;

  std::string _name;
  long _id;
  int _num_limbs;
};

bool operator==(const Pet &pet1, const Pet &pet2);

bool operator!=(const Pet &pet1, const Pet &pet2);

std::ostream &operator<<(std::ostream &os, const Pet &pet);
