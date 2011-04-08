
#ifndef _Matrix_Property_Operation_H_
#define _Matrix_Property_Operation_H_

#include "vector/interface.h"
#include "matrix/base/property-name.h"
#include "matrix/transpose-name.h"
#include "matrix/data-order-name.h"

namespace mysimulator {

  void _ProduceActualDataOrder(Vector<int>& p) {
    if(p[MatrixTranspose]==NoTranspose)
      p[MatrixTranspose]=p[MatrixDataOrder];
    else if(p[MatrixTranspose]==Transposed) {
      if(p[MatrixDataOrder]==OrderC) p[MatrixActualOrder]=OrderFortran;
      else if(p[MatrixDataOrder]==OrderFortran) p[MatrixActualOrder]=OrderC;
      else if(p[MatrixDataOrder]==OrderDiagonal)
        p[MatrixActualOrder]=OrderDiagonal;
      else Error("Unknown Data-Order Name in Data-Order Product!");
    } else Error("Unknown Transpose Format in Data-Order Product!");
  }

}

#endif

