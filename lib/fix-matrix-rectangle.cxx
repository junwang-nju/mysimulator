
#include "fix-matrix-rectangle.h"

namespace std {

  template <typename T, unsigned int NR, unsigned int NC, int Ord, int Trans,
            int DOrd, unsigned int NL, unsigned int ML>
  void fixRectMatrix<T,NR,NC,Ord,Trans,DOrd,NL,ML>::clear() {
    myError("fix rectangle matrix cannot be cleared!");
  }

  template <typename T, unsigned int NR, unsigned int NC, int Ord, int Trans,
            int DOrd, unsigned int NL, unsigned int ML>
  const char* fixRectMatrix<T,NR,NC,Ord,Trans,DOrd,NL,ML>::type() const {
    return "fixed rectangle matrix";
  }

}

