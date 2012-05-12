
#ifndef _Interaction_Func_Impl_Dihedral_Periodic_Func_H_
#define _Interaction_Func_Impl_Dihedral_Periodic_Func_H_

#include "interaction/func/impl/dihedral/periodic/parameter/name.h"
#include "interaction/func/impl/dihedral/periodic/buffer/post-name.h"
#include "intrinsic-type/cosine.h"

namespace mysimulator {

  template <typename T>
  void FuncDihedralPeriodic(const Array1D<T>& post,
                            const Array1D<Unique64Bit>& P,T* func) {
    T fc=0;
    Unique64Bit *Q=const_cast<Unique64Bit*>(P.start)+
                   DihedralPeriodicFuncParamShift;
    T dih=pos[DihedralValue];
    T theta;
    for(unsigned int i=0;i<P[DihedralPeriodicNumFuncs].u;++i) {
      theta=dih+Q[DihedralPeriodicFuncPhase].value<T>();
      theta*=Q[DihedralPeriodicFuncFrequency].u;
      fc+=Q[DihedralPeriodicFuncStrength].value<T>()*(Cosine(theta)+1.);
      Q+=DihedralPeriodicFuncNumberParameters;
    }
    *func=fc;
  }

}

#endif

