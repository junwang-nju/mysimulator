
#ifndef _Reference_Matrix_Triangle_H_
#define _Reference_Matrix_Triangle_H_

#include "matrix-triangle.h"

namespace std {

  template <typename T>
  class refMatrixTriangle : public TriangMatrix<T,refVector> {

    public:

      typedef TriangMatrix<T,refVector>   Type;

  };

}

#endif

