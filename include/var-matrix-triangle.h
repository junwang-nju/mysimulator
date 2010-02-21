
#ifndef _Variable_Matrix_Triangle_H_
#define _Variable_Matrix_Triangle_H_

#include "object-with-storage.h"
#include "matrix-triangle-base.h"
#include "var-vector.h"

namespace std {

  template <typename T>
  class varTriangMatrix
    : public ObjectWStorage<TriangMatrixBase<T,varVector> > {
  };

}

#endif
