#include <iostream>
#include <vector>
template <typename T> class PrettyPrinter {
  T *m_pData;

public:
  PrettyPrinter(T *data) : m_pData(data) {}
  void Print() { std::cout << "{" << *m_pData << "}" << std::endl; }

  T *GetData() { return m_pData; }
};

// Explicit specialization of a member function should appear outside the class
template <> void PrettyPrinter<std::vector<ll>>::Print() {
  std::cout << "{";
  for (const auto &x : *m_pData) {
    std::cout << x;
  }
  std::cout << "}" << std::endl;
}
template <> class PrettyPrinter<char *> {
  char *m_pData;

public:
  PrettyPrinter(char *data) : m_pData(data) {}
  void Print() { std::cout << "{" << m_pData << "}" << std::endl; }
  char *GetData() { return m_pData; }
};

// template<>
// class PrettyPrinter<std::vector<ll>> {
//	std::vector<ll> *m_pData;
// public:
//	PrettyPrinter(std::vector<ll> *data) :m_pData(data) {
//
//	}
//	void Print() {
//		std::cout << "{";
//		for (const auto &x : *m_pData) {
//			std::cout << x;
//		}
//		std::cout << "}" << std::endl;
//	}
//	std::vector<ll> * GetData() {
//		return m_pData;
//	}
//};
int main() {
  // ll data = 5;
  // float f = 8.2f;
  // PrettyPrinter<ll> p1(&data);
  // p1.Print();
  // PrettyPrinter<float> p2(&f);
  // p2.Print();

  char *p{"Hello world"};
  PrettyPrinter<char *> p3(p);
  p3.Print();
  char *pData = p3.GetData();
  std::vector<ll> v{1, 2, 3, 4, 5};
  PrettyPrinter<std::vector<ll>> pv(&v);
  pv.Print();
  return 0;
}
