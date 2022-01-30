#include <iostream>
#include <vector>

// Primary or base template
template <typename T, ll columns> class PrettyPrinter {
  T *m_pData;

public:
  PrettyPrinter(T *data) : m_pData(data) {}
  void Print() {
    std::cout << "Columns:" << columns << std::endl;
    std::cout << "{" << *m_pData << "}" << std::endl;
  }

  T *GetData() { return m_pData; }
};
// Partial specialization for value 80
template <typename T> class PrettyPrinter<T, 80> {
  T *m_pData;

public:
  PrettyPrinter(T *data) : m_pData(data) {}
  void Print() {
    std::cout << "Using 80 Columns" << std::endl;
    std::cout << "{" << *m_pData << "}" << std::endl;
  }

  T *GetData() { return m_pData; }
};
template <typename T> class SmartPointer {
  T *m_ptr;

public:
  SmartPointer(T *ptr) : m_ptr(ptr) {}
  T *operator->() { return m_ptr; }
  T &operator*() { return *m_ptr; }
  ~SmartPointer() { delete m_ptr; }
};
// Partial specialization for array types
template <typename T> class SmartPointer<T[]> {
  T *m_ptr;

public:
  SmartPointer(T *ptr) : m_ptr(ptr) {}
  T &operator[](ll index) { return m_ptr[index]; }
  ~SmartPointer() { delete[] m_ptr; }
};
int main() {
  ll data = 800;
  PrettyPrinter<ll, 80> p{&data};
  p.Print();
  SmartPointer<ll[]> s1{new ll[5]};
  s1[0] = 5;
  std::cout << s1[0] << std::endl;
  return 0;
}
