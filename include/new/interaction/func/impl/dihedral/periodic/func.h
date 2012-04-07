
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Func_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Func_H_

#include "interaction/func/impl/dihedral/periodic/parameter/name.h""
#include "interaction/func/impl/dihedral/periodic/buffer/name.h""
#include "intrinsic-type/cos.h"

namespace mysimulator {

  template <typename T>
  void FuncDihedralPeriodic(const T* buf, const Unique64Bit* P, T* func) {
    T fc=0;
    Unique64Bit *Q=const_cast<Unique64Bit*>(P)+DihedralPeriodicFuncParamShift;
    T dih=buf[DihedralValue];
    T theta;
    for(unsigned int i=0;i<P[DihedralPeriodicNumFuncs].value<unsigned int>();
        ++i) {
      theta=dih+Q[DihedralPeriodicFuncPhase].value<T>();
      theta*=Q[DihedralPeriodicFuncFrequence].value<unsigned int>();
      fc+=Q[DihedralPeriodicFuncStrength].value<T>()*(Cosine(theta)+1.);
      Q+=DihedralPeriodicFuncNumberParameters;
    }
    *func=fc;
  }

}

#endif

