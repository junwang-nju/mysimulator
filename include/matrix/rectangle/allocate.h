
#ifndef _Matrix_Rectangle_Allocate_H_
#define _Matrix_Rectangle_Allocate_H_

#include "matrix/interface.h"
#include "matrix/data-order-name.h"
#include "matrix/rectangle/property-name.h"
#include "matrix/type-name.h"
#include "matrix/property/op.h"
#include "matrix/rectangle/get-func.h"

namespace mysimulator {

  template <typename T>
  void allocateMatrixRectangle(
      Matrix<T>& M, const unsigned int nr, const unsigned int nc,
      const unsigned int DOrder, const unsigned int TransposeForm) {
    assert(DOrder!=OrderDiagonal);
    release(M);
    allocate(M.property,NumberMatrixRectangleProperty);
    M.property[MatrixType]=MatrixRectangle;
    M.property[MatrixNumberRows]=nr;
    M.property[MatrixNumberColumns]=nc;
    M.property[MatrixNumberElements]=nr*nc;
    M.property[MatrixDataOrder]=DOrder;
    M.property[MatrixTranspose]=TransposeForm;
    _ProduceActualDataOrder(M.property);
    Vector<unsigned int> sz;
    if(M.property[MatrixActualOrder]==OrderC) {
      allocate(sz,nr);
      fill(sz,nc);
      M.GetFunc=MatrixRect_Get4C<T>;
    } else if(M.property[MatrixActualOrder]==OrderFortran) {
    } else Error("Improper Data Order in allocating Rectangle Matrix!");
    allocate(static_cast<List<T>&>(M),sz);
  }

}

#endif

