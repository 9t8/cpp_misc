#include <bits/stdc++.h>

#include "Queue.h"

int main() {
  const int DUMMY_ELEM = 0xDEADBEEF;
  size_t size = 5;
  Queue<int> q(size);
  std::cout << "Start with Empty queue test\n";
  std::cout << q.to_string();
  assert(q.is_empty() == true);
  assert(q.dequeue() == false);
  // Despite what the spec says, this is the correct test
  assert(q.size() == 0);
  // Empty queue returns the sentinel
  assert(q.peek() == Queue<int>::get_sentinel());
  // For a queue of integers, initial sentinel is zero
  assert(q.get_sentinel() == 0);
  // round trip sentinel
  Queue<int>::set_sentinel(-1);
  assert(q.get_sentinel() == -1);
  // Restore _sentinel to default for ints
  Queue<int>::set_sentinel(0);

  std::cout << "\nAdd elements with catchy values...\n";
  size_t elem = 100;
  size_t inc = 100;
  for (int i = 0; i < 5; ++i) {
    assert(q.enqueue(elem + i * inc) == true);
  }
  std::cout << q.to_string() << "\n";

  std::cout << "Queue is full, next enqueue needs to fail \n\n";
  assert(q.is_empty() == false);
  assert(q.enqueue(DUMMY_ELEM) == false);

  std::cout << "Yes, it failed as expected\n";

  // Let's complicate and remove first two elements
  // When de-queueing do you set the element to which value? Auto-grader does
  // not really test for this
  assert(q.dequeue() == true);
  assert(q.dequeue() == true);
  // enqueuing two more elements will test circling back to beginning of vector
  for (int i = 5; i < 7; ++i) {
    assert(q.enqueue(elem + i * inc) == true);
  }

  // Queue is full, next enqueue needs to fail
  assert(q.is_empty() == false);
  assert(q.enqueue(DUMMY_ELEM) == false);

  std::cout << "Test if your to_string know how to wrap around the vector \n\n";
  std::cout << q.to_string();

  std::cout << "\nTesting resize. There are three main cases: \n";
  std::cout << "Resizing with gt, eq or lt values\n";

  std::cout << "1 - Resizing to same size...\n";
  q.resize(5);  // equal size, nothing should happen

  std::cout << "2 - Resizing to a larger size...and limit printing\n";
  q.resize(10);  // larger
  // Now add elements
  for (int i = 7; i < 9; ++i) {
    assert(q.enqueue(elem + i * inc) == true);
  }

  std::cout << q.to_string(3) << "\n";

  std::cout << "3 - Resizing to a less size then original...\n";
  // The transition from larger to less than original (size 5) is tricky. You
  // might be tempted at just blindly resize vector but that will not work in
  // many corner cases. Paper and pen are your friends here
  q.resize(2);  // less

  std::cout << "Done with main tests\n";

  std::cout << "\n\n\n";
  std::cout << "Testing Pop-a-Lot, queue with 5 elements\n";

  Queue<int> qPop(size);
  for (int i = 0; i < 5; ++i) {
    assert(qPop.enqueue(elem + i * inc) == true);
  }
  std::cout << qPop.to_string() << "\n";
  popalot(qPop);
  assert(qPop.size() == 0);
  std::cout << "After Pop-a-Lot, no elements\n";
  std::cout << qPop.to_string();
}
