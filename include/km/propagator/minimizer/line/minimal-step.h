
#ifndef _Propagator_Minimizer_Line_MinimalStep_H_
#define _Propagator_Minimizer_Line_MinimalStep_H_

#include "array2d-numeric/interface.h"
#include "basic/constant.h"

namespace mysimulator {

  template <typename T>
  T MinimalStep(const Array2DBase<T>& X, const Array2DBase<T>& Dirc,
                const unsigned int DOF) {
    typedef typename IsFloatPoint<T>::Type  FloatCheck;
    assert(X.IsValid());
    assert(Dirc.IsValid());
    assert(IsSameSize(X,Dirc));
    T mstep,tmd1,tmd2;
    const unsigned int n=X._ldata.Size();
    for(unsigned int i=0;i<n;++i) {
      tmd1=AbsVal(X._ldata[i]);
      tmd2=Dirc._ldata[i];
      tmd1=(tmd1<1?tmd2:tmd2/tmd1);
      mstep+=tmd*tmd;
    }
    assert(mstep>0);
    return _RelDelta<T>()*__SqRoot(DOF/mstep);
  }

}

#endif

