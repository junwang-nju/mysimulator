
#ifndef _Reference_Matrix_Rectangle_H_
#define _Reference_Matrix_Rectangle_H_

#include "matrix-rectangle.h"

namespace std {

  template <typename T>
  class refMatrixRectangle : public RectMatrix<T,refVector> {

    public:

      typedef RectMatrix<T,refVector>     Type;

  };

}

#endif

