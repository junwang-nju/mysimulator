
#include "matrix-base.h"

namespace std {

  template <typename T>
  void MatrixBase<T>::clear() {
    getUnit=NULL;
    NRow=NCol=uZero;
    Order=UnknownOrder;
    Transpose=UnknownTranspose;
    DataOrder=UnknownOrder;
    Data.clear();
    Lines.clear();
  }

  template <typename T>
  varVector<T>& MatrixBase<T>::data() { return Data; }

  template <typename T>
  const varVector<T>& MatrixBase<T>::data() const { return Data; }

  template <typename T>
  T& MatrixBase<T>::operator()(unsigned int I, unsigned int J) {
    return getUnit(Lines,I,J);
  }

  template <typename T>
  const T& MatrixBase<T>::operator()(unsigned int I, unsigned int J) const {
    return getUnit(Lines,I,J);
  }

}

