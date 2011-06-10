
#ifndef _Matrix_Storage_Item_Allocate_H_
#define _Matrix_Storage_Item_Allocate_H_

#include "matrix/storage/item/interface.h"

namespace mysimulator {

  template <typename T>
  void allocate(MatrixStorageItem<T>& U) { release(U); }

  template <typename T>
  void imprint(MatrixStorageItem<T>& U,const MatrixStorageItem<T>&) {
    allocate(U);
  }

}

#endif

