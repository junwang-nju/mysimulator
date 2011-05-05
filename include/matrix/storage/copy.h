
#ifndef _Matrix_Storage_Copy_H_
#define _Matrix_Storage_Copy_H_

#include "matrix/storage/interface.h"
#include <cstring>

namespace mysimulator {

  template <typename T>
  void copy(MatrixStorage<T>& S, const MatrixStorage<T>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    S.status()=cS.status();
    copy(S.data,cS.data);
  }

  template <typename T>
  void ecopy(MatrixStorage<T>& S, const MatrixStorage<T>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    assert(IsPropertySame(S.data,cS.data));
    S.status()=cS.status();
    unsigned int n=sizeof(MatrixStorageItem<T>)/sizeof(char);
    n*=cS.data.property[MatrixNumberElements];
    memcpy(S.data.pdata,cS.data.pdata,n);
  }

}

#endif

