
#ifndef _Interaction_Func_Impl_Dihedral_Periodic_Diff_H_
#define _Interaction_Func_Impl_Dihedral_Periodic_Diff_H_

#include "interaction/func/impl/dihedral/periodic/parameter/name.h"
#include "interaction/func/impl/dihedral/periodic/buffer/post-name.h"
#include "intrinsic-type/sine.h"

namespace mysimulator {

  template <typename T>
  void DiffDihedralPeriodic(const Array1D<T>& post,
                            const Array1D<Unique64Bit>& P, T* diff) {
    T df=0;
    Unique64Bit *Q=const_cast<Unique64Bit*>(P._data)+
                   DihedralPeriodicFuncParamShift;
    T dih=post[DihedralValue];
    T theta;
    for(unsigned int i=0;i<P[DihedralPeriodicNumFuncs].u;++i) {
      theta=dih+Value<T>(Q[DihedralPeriodicFuncPhase]);
      theta*=Q[DihedralPeriodicFuncFrequency].u;
      df-=Value<T>(Q[DihedralPeriodicFuncStrengthFrequency])*Sine(theta);
      Q+=DihedralPeriodicFuncNumberParameters;
    }
    *diff=df;
  }

}

#endif

