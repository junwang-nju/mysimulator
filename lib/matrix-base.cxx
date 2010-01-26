
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
  const unsigned int& MatrixBase<T>::NumberRow() const { return NRow; }

  template <typename T>
  const unsigned int& MatrixBase<T>::NumberColumn() const { return NCol; }

  template <typename T>
  const int& MatrixBase<T>::MatrixOrder() const { return Order; }

  template <typename T>
  const int& MatrixBase<T>::MatrixTransposeStatus() const { return Transpose; }

  template <typename T>
  const int& MatrixBase<T>::MatrixDataOrder() const { return DataOrder; }

  template <typename T>
  void MatrixBase<T>::SetSize(const unsigned int NR, const unsigned int NC) {
    NRow=NR;
    NCol=NC;
  }

  template <typename T>
  void MatrixBase<T>::SetMatrixOrder(const int MOrd) { Order=MOrd; }

  template <typename T>
  void MatrixBase<T>::SetMatrixTransposeStatus(const int MTrans) {
    Transpose=MTrans;
  }

  template <typename T>
  void MatrixBase<T>::SetDataOrder(const int DOrd) { DataOrder=DOrd; }

  template <typename T>
  void MatrixBase<T>::AssignGetMethod(
      const MatrixBase<T>::GetUnitType& iGetUnit) {
    getUnit=iGetUnit;
  }

  template <typename T>
  T& MatrixBase<T>::operator()(unsigned int I, unsigned int J) {
    return getUnit(Lines,I,J);
  }

  template <typename T>
  const T& MatrixBase<T>::operator()(unsigned int I, unsigned int J) const {
    return getUnit(Lines,I,J);
  }

}

