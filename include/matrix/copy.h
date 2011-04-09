
#ifndef _Matrix_Copy_H_
#define _Matrix_Copy_H_

#include "matrix/interface.h"
#include "matrix/property/assign-check.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename T, typename cT>
  void copy(Matrix<T>& M, const Matrix<cT>& cM,
            const int nr=iNOne,             const int nc=iNOne,
            const unsigned int mrb=uZero,   const unsigned int mrs=uOne,
            const unsigned int mcb=uZero,   const unsigned int mcs=uOne,
            const unsigned int crb=uZero,   const unsigned int crs=uOne,
            const unsigned int ccb=uZero,   const unsigned int ccs=uOne) {
    assert(IsValid(M)&&IsValid(cM));
    assert(AssignCheck(M.property,cM.property));
    unsigned int nrow,ncol;
    nrow=(nr>0?nr:
         (M.property[MatrixNumberRows]<cM.property[MatrixNumberRows]?
          M.property[MatrixNumberRows]:cM.property[MatrixNumberRows]));
    ncol=(nc>0?nc:
         (M.property[MatrixNumberColumns]<cM.property[MatrixNumberColumns]?
          M.property[MatrixNumberColumns]:cM.property[MatrixNumberColumns]));
    assert(mrb+nrow*mrs<=M.property[MatrixNumberRows]);
    assert(crb+nrow*crs<=cM.property[MatrixNumberRows]);
    assert(mcb+ncol*mcs<=M.property[MatrixNumberColumns])
    assert(ccb+ncol*ccs<=cM.property[MatrixNumberColumns]);
    for(unsigned int i=0,mr=mrb,cr=crb;i<nrow;++i,mr+=mrs,cr+=crs)
    for(unsigned int j=0,mc=mcb,cc=ccb;j<ncol;++j,mc+=mcs,cc+=ccs)
      copy(M(mr,mc),cM(cr,cc));
  }

}

#include "matrix/compare.h"
#include "vector/copy.h"

namespace mysimulator {

  template <typename T, typename cT>
  void ecopy(Matrix<T>& M, const Matrix<T>& cM) {
    assert(IsPropertySame(M,cM));
    copy(static_cast<Vector<T>&>(M),static_cast<const Vector<T>&>(cM));
  }

}

#endif

