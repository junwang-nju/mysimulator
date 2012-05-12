
#ifndef _Interaction_Func_Impl_Dihedral_Periodic_Both_H_
#define _Interaction_Func_Impl_Dihedral_Periodic_Both_H_

#include "interaction/func/impl/dihedral/periodic/parameter/name.h"
#include "interaction/func/impl/dihedral/periodic/buffer/post-name.h"
#include "intrinsic-type/cosine.h"
#include "intrinsic-type/sine.h"

namespace mysimulator {

  template <typename T>
  void BothDihedralPeriodic(const Array1D<T>& post,
                            const Array1D<Unique64Bit>& P,T* func,T* diff) {
    T fc=0, df=0;
    T dih=post[DihedralValue];
    T theta;
    Unique64Bit *Q=const_cast<Unique64Bit*>(P.start)+
                   DihedralPeriodicFuncParamShift;
    for(unsigned int i=0;i<P[DihedralPeriodicNumFuncs].u;++i) {
      theta=dih+Q[DihedralPeriodicFuncPhase].value<T>();
      theta*=Q[DihedralPeriodicFuncFrequency].u;
      fc+=Q[DihedralPeriodicFuncStrength].value<T>()*(Cosine(theta)+1.);
      df+=Q[DihedralPeriodicFuncStrengthFrequency].value<T>()*Sine(theta);
      Q+=DihedralPeriodicFuncNumberParameters;
    }
    *func=fc;
    *diff=df;
  }

}

#endif

