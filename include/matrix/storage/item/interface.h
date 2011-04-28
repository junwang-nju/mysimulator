
#ifndef _Matrix_Storage_Item_Interface_H_
#define _Matrix_Storage_Item_Interface_H_

#include "intrinsic-type/validity-check.h"

namespace mysimulator {

  template <typename T>
  struct MatrixStorageItem {

    typedef MatrixStorageItem<T>    Type;

    T content;
    unsigned int status;

    MatrixStorageItem() : content(), status(0) {}
    MatrixStorageItem(const Type&) {
      Error("Copier of MatrixStorageItem Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for MatrixStorageItem Disabled!");
      return *this;
    }
    ~MatrixStorageItem() { clearData(); }

    void clearData() { status=0; }

  };

  template <typename T>
  bool IsValid(const MatrixStorageItem<T>& U) { return IsValid(U.content); }

  template <typename T>
  void release(MatrixStorageItem<T>& U) { U.clearData(); }

}

#endif

