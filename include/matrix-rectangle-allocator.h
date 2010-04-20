
#ifndef _Matrix_Rectangle_Allocator_H_
#define _Matrix_Rectangle_Allocator_H_

#include "matrix.h"

namespace std {

  template <typename T>
  T& GetData4C(T** structure, const unsigned int I, const unsigned int J,T&) {
    return structure[I][J];
  }

  template <typename T>
  T& GetData4F(T** structure, const unsigned int I, const unsigned int J,T&) {
    return structure[J][I];
  }

  enum MatrixRectanglePropertyName {
    MatrixRectangleNumberProperty=MatrixCommonNumberProperty
  };

  template <typename T>
  void allocateRectangleMatrix(
      Matrix<T>& M, const unsigned int nRow, const unsigned int nCol,
                    const unsigned int DataOrder,
                    const unsigned int TransposeForm) {
    assert(DataOrder!=DiagonalOrder);
    M.property=new unsigned int[MatrixRectangleNumberProperty];
    M.property[MatrixNumberRow]=nRow;
    M.property[MatrixNumberColumn]=nCol;
    M.property[MatrixNumberElement]=nRow*nCol;
    M.property[MatrixDataOrder]=DataOrder;
    M.property[MatrixTransposeForm]=TransposeForm;
    SetMatrixActualOrder(M.property);
    M.data=new T[M.property[MatrixNumberElement]];
    T* PtrData=M.data;
    if(M.property[MatrixActualOrder]==COrder) {
      M.structure=new T*[nRow];
      for(unsigned int i=0;i<nRow;++i,PtrData+=nCol)  M.structure[i]=PtrData;
      M.GetFunc=GetData4C<T>;
    } else if(M.property[MatrixActualOrder]==FortranOrder) {
      M.structure=new T*[nCol];
      for(unsigned int i=0;i<nCol;++i,PtrData+=nRow)  M.structure[i]=PtrData;
      M.GetFunc=GetData4F<T>;
    } else myError("Unknown or Unimplemented Data Order of Matrix");
    M.PtrOtherElement=NULL;
  }

}

#endif

