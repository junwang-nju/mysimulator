
#include "matrix-triangle.h"

namespace std {

  template <typename T>
  const unsigned int& triangMatrix<T>::dimension() const {
    return this->NumberRow();
  }

  template <typename T>
  void triangMatrix<T>::SetSymmetry(const int SF) {
    SymFlag=SF;
    if(SymFlag==NoSymmetry) {
    } else if(SymFlag==Symmetric) {
    } else myError("Unknown Symmetry flag for triangle matrix");
  }

  template <typename T>
  void triangMatrix<T>::clear() {
    static_cast<ParentType*>(this)->clear();
    HalfPart=UnknownPart;
    SymFlag=UnknownSym;
    Nullify(OtherObj);
  }

  template <typename T>
  const char* triangMatrix<T>::type() { return "Triangle Matrix"; }

}

