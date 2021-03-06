
#ifndef _Matrix_Storage_Allocate_H_
#define _Matrix_Storage_Allocate_H_

#include "matrix/storage/interface.h"
#include "matrix/allocate.h"
#include "matrix/storage/item/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(MatrixStorage<T>& S, const unsigned int n) {
    release(S);
    allocate(S.data,MatrixTriangle,n,OrderC,Transposed,UpperTriangle,
             true,false);
    S.status()=1;
  }

  template <typename T>
  void imprint(MatrixStorage<T>& S, const MatrixStorage<T>& sS) {
    imprint(S.data,sS.data);
    S.status()=1;
  }

}

#endif

