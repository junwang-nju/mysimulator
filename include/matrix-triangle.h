
#ifndef _Matrix_Triangle_H_
#define _Matrix_Triangle_H_

#include "matrix-base.h"

namespace std {
  enum TriangleMatrixPart {
    UnknowPart=-1,
    UpperPart,
    LowerPart
  };
  template <typename T>
  class triangMatrix : public MatrixBase<T> {
    protected:
      int HalfPart;
    public:
      typedef T   DataType;
      typedef triangMatrix<T>   Type;
      typedef MatrixBase<T>     ParentType;
      triangMatrix() : ParentType(), HalfPart(UnknowPart) {}
      triangMatrix(const unsigned int N, int Ord=COrder, int Trans=Original,
                   int Hf=UpperPart) {
        allocate(N,Ord,Trans,Hf);
      }
      virtual ~triangMatrix() { HalfPart=UnknowPart; }
  };
}

#endif

