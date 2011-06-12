
#ifndef _Matrix_Allocate_H_
#define _Matrix_Allocate_H_

#include "matrix/rectangle/allocate.h"
#include "matrix/triangle/allocate.h"
#include "vector/copy.h"
#include <cstdarg>

namespace mysimulator {

  template <typename T>
  void allocate(Matrix<T>& M, const unsigned int MType, ...) {
    va_list vl;
    va_start(vl,MType);
    if(MType==MatrixRectangle) {
      unsigned int nrow=va_arg(vl,unsigned int);
      unsigned int ncol=va_arg(vl,unsigned int);
      unsigned int dorder=va_arg(vl,unsigned int);
      unsigned int tform=va_arg(vl,unsigned int);
      allocateMatrixRectangle(M,nrow,ncol,dorder,tform);
    } else if(MType==MatrixTriangle) {
      unsigned int dim=va_arg(vl,unsigned int);
      unsigned int dorder=va_arg(vl,unsigned int);
      unsigned int tform=va_arg(vl,unsigned int);
      unsigned int tpart=va_arg(vl,unsigned int);
      bool sflag=static_cast<bool>(va_arg(vl,int));
      bool dflag=static_cast<bool>(va_arg(vl,int));
      allocateMatrixTriangle(M,dim,dorder,tform,tpart,sflag,dflag);
    } else Error("Unknown Matrix Type in allocation!");
    va_end(vl);
  }

  template <typename T>
  void imprint(Matrix<T>& M, const Matrix<T>& cM) {
    assert(IsValid(cM));
    imprint(static_cast<List<T>&>(M),static_cast<const List<T>&>(cM));
    imprint(M.property,cM.property);
    copy(M.property,cM.property);
    M.GetFunc=cM.GetFunc;
    if(IsValid(cM.other)) imprint(M.other,cM.other);
  }

}

#endif

