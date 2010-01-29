
#ifndef _Matrix_Base_H_
#define _Matrix_Base_H_

#include "data-pack.h"

namespace std {
  enum MatrixFormat {
    UnknownFormat=-1,
    Rectangle,
    Square,
    Triangle,
    Band,
    TriangleBand,
    NumberMatrixFormat
  };
  enum MatrixDataOrder {
    UnknownOrder=-1,
    COrder,
    FortranOrder,
    DiagonalOrder,
    NumberMatrixDataOrder
  };
  enum CommonInfoItems {
    MatrixType=0,
    ExpectOrder,
    TransposeState,
    ActualOrder,
    NumberRows,
    NumberColumns
  };
  template <typename T, template<typename> class VecType>
  class MatrixBase : DataPack<T,VecType,VecType,VecType> {
    public:
      typedef T   DataType;
      typedef MatrixBase<T,VecType>   Type;
      typedef DataPack<T,VecType,VecType,VecType> ParentType;
      typedef T& (*GetElemFuncType)(VecType<refVector<T> >&,
                                    unsigned int,unsigned int);
    protected:
      T OtherElems;
      GetElemFuncType getElem;
    public:
      MatrixBase() : ParentType(), OtherElems(), getElem(NULL) {}
  };
}

#endif

