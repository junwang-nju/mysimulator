
#include "fix-vector.h"

namespace std {

  template <typename T, unsigned int ND>
  void fixVector<T,ND>::clear() { }

  template <typename T, unsigned int ND>
  const char* fixVector<T,ND>::type() const { return "Fixed Vector"; }

}
