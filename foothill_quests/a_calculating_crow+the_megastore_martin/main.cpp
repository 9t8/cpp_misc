#include "Pet.h"
#include "Pet_Store.h"

#include <bits/stdc++.h>

using namespace std;

int main() {
  Pet_Store pet_store(20);
  pet_store.populate_with_n_random_pets(20);
  int id;
  cin >> id;
  Pet pet;
  cout << pet_store.find_pet_by_id_bin(id, pet) << '\n';
}
