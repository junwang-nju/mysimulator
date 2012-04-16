
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Both_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Both_H_

#include "interaction/func/impl/dihedral/periodic/parameter/name.h"
#include "interaction/func/impl/dihedral/periodic/buffer/post-name.h"
#include "intrinsic-type/cos.h"
#include "intrinsic-type/sin.h"

namespace mysimulator {

  template <typename T>
  void BothDihedralPeriodic(const T* post,const Unique64Bit* P,T* func,T* diff){
    T fc=0., df=0.;
    T dih=post[DihedralValue];
    T theta;
    Unique64Bit* Q=const_cast<Unique64Bit*>(P)+DihedralPeriodicFuncParamShift;
    for(unsigned int i=0;i<P[DihedralPeriodicNumFuncs].value<unsigned int>();
        ++i) {
      theta=dih+Q[DihedralPeriodicFuncPhase].value<T>();
      theta*=Q[DihedralPeriodicFuncFrequence].value<unsigned int>();
      fc+=Q[DihedralPeriodicFuncStrength].value<T>()*(Cosine(theta)+1.);
      df-=Q[DihedralPeriodicFuncStrengthFrequence].value<T>()*Sine(theta);
      Q+=DihedralPeriodicFuncNumberParameters;
    }
    *func=fc;
    *diff=df;
  }

}

#endif

