
#ifndef _Variable_Matrix_Triangle_H_
#define _Variable_Matrix_Triangle_H_

#include "matrix-triangle.h"

namespace std {

  template <typename T>
  class varMatrixTriangle : public TriangMatrix<T,varVector> {

    public:

      typedef TriangMatrix<T,varVector>   Type;

  };

}

#endif

