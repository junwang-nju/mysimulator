
#ifndef _Double_Vector_H_
#define _Double_Vector_H_

#include "vector-base.h"
#include "blas.h"
#include "memory.h"
#include "util.h"
#include <cassert>

namespace std {

  struct DbVector : public VectorBase {

    typedef DbVector    Type;
    typedef VectorBase  ParentType;

    double* data;

    DbVector() : ParentType(), data(NULL) {}
    DbVector(const Type& dv) : ParentType() {}
    Type& operator=(const Type& dV) {
      assert(IsAvailable(data));
      assert(IsAvailable(dV.data));
      static long n=(size<dV.size?size:dV.size);
      dcopy_(&n,data,const_cast<long*>(&lOne),
                const_cast<double*>(dV.data),const_cast<long*>(&lOne));
    }
    ~DbVector() { safe_release(data,state); }

  };

}

#endif

