
#ifndef _Matrix_Storage_Item_Copy_H_
#define _Matrix_Storage_Item_Copy_H_

#include "matrix/storage/item/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T>
  void copy(MatrixStorageItem<T>& U, const MatrixStorageItem<T>& cU) {
    copy(U.content,cU.content);
    copy(U.status,cU.status);
  }

}

#endif

