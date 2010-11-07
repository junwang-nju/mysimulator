
#ifndef _Matrix_Rectangle_Allocator_H_
#define _Matrix_Rectangle_Allocator_H_

#include "data/name/matrix-rectangle-name.h"

namespace std {

  template <typename T>
  struct Matrix;

  template <typename T>
  T& GetData4C(Vector<T>* s, const int I, const int J, T&) { return s[I][J]; }

  template <typename T>
  T& GetData4F(Vector<T>* s, const int I, const int J, T&) { return s[J][I]; }

  template <typename T>
  void allocateRectangleMatrix(Matrix<T>& M,
                               const int nRow, const int nCol,
                               const int DOrder, const int TForm) {
    assert(DOrder!=DiagonalOrder);
    allocate(M.property,MatrixRectangleNumberProperty);
    M.property[MatrixType]=RectangleMatrix;
    M.property[MatrixNumberRow]=nRow;
    M.property[MatrixNumberColumn]=nCol;
    M.property[MatrixNumberElement]=nRow*nCol;
    M.property[MatrixDataOrder]=DOrder;
    M.property[MatrixTransposeForm]=TForm;
    M.SetActualOrder();
    Vector<unsigned int> sz;
    if(M.property[MatrixActualOrder]==COrder) {
      allocate(sz,nRow);
      copy(sz,nCol);
      M.GetFunc=GetData4C<T>;
    } else if(M.property[MatrixActualOrder]==FortranOrder) {
      allocate(sz,nCol);
      copy(sz,nRow);
      M.GetFunc=GetData4F<T>;
    } else myError("Unknown Data Order");
    allocate(static_cast<PropertyList<T>&>(M),sz);
    M.ptrOther=NULL;
  }

}

#endif
