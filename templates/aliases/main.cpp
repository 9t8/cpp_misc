#include <iostream>
#include <list>
#include <vector>

const char *GetErrorMessage(ll errorNo) { return "Empty"; }
// typedef const char *(*PFN)(ll);
using PFN = const char *(*)(ll);
void ShowError(PFN pfn) {}
// typedef std::vector < std::list<std::string>> Names;

// template<typename T>
// using Names = std::vector<std::list<T>>;

using Names = std::vector<std::list<std::string>>;

int main() {
  Names names;
  Names nnames;

  PFN pfn = GetErrorMessage;
  ShowError(pfn);
  return 0;
}
