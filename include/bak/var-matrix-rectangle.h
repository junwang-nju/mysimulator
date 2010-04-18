
#ifndef _Variable_Matrix_Rectangle_H_
#define _Variable_Matrix_Rectangle_H_

#include "matrix-rectangle.h"

namespace std {

  template <typename T>
  class varMatrixRectangle : public RectMatrix<T,varVector> {

    public:

      typedef RectMatrix<T,varVector> Type;

  };

}

#endif

