
#ifndef _Matrix_Base_Interface_H_
#define _Matrix_Base_Interface_H_

#include "array/2d/interface.h"
#include "matrix/storage-name.h"

namespace mysimulator {

  template <typename T>
  struct MatrixBase : public Array2D<T> {

    public:

      typedef MatrixBase<T>   Type;
      typedef Array2D<T>      ParentType;

      unsigned int      NumRows;
      unsigned int      NumColumns;
      MatrixStorageName StorageName;

      MatrixBase() : ParentType(), NumRows(0), NumColumns(0),
                     StorageName(MatrixStorageUnknown) {}
      ~MatrixBase() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               (NumRows>0)&&(NumColumns>0)&&(StorageName!=MatrixStorageUnknown);
      }

  };

  template <typename T>
  void Clear(MatrixBase<T>& M) {
    Clear(static_cast<typename MatrixBase<T>::ParentType&>(M));
    M.NumRows=0;
    M.NumColumns=0;
    M.StorageName=MatrixStorageUnknown;
  }

}

#endif

