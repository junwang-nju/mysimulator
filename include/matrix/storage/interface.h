
#ifndef _Matrix_Storage_Interface_H_
#define _Matrix_Storage_Interface_H_

#include "matrix/storage/item/interface.h"
#include "matrix/interface.h"

namespace mysimulator {

  template <typename T>
  struct MatrixStorage : public Matrix<MatrixStorageItem<T> > {

    typedef MatrixStorage<T>    Type;
    typedef MatrixStorageItem<T>  ParentType;

    unsigned int gstatus;

    MatrixStorage() : ParentType(), gstatus(1) {}
    MatrixStorage(const Type&) { Error("Copier for MatrixStorage Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MatrixStorage Disabled!");
      return *this;
    }
    ~MatrixStorage() { clearData(); }

    void clearData() {
      static_cast<ParentType*>(this)->clearData();
      gstatus=1;
    }

  };

  template <typename T>
  void release(MatrixStorage<T>& S) { S.clearData(); }

}

#endif

