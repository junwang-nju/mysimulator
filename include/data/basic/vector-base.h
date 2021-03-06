
#ifndef _Vector_Base_H_
#define _Vector_Base_H_

#include "data/name/constant.h"
#include "data/name/storage-state.h"
#include "operation/basic/error-op.h"

namespace std {

  struct VectorBase {

    typedef VectorBase  Type;
    
    unsigned int size;
    unsigned int state;
    
    VectorBase() : size(uZero), state(Unused) {}
    VectorBase(const Type& VB) {
      Error("Cannot create base class of vector");
    }
    Type& operator=(const Type& VB) {
      Error("Cannot copy base class of vector");
      return *this;
    }
    ~VectorBase() { size=uZero; state=Unused; }

  };

}

#endif
