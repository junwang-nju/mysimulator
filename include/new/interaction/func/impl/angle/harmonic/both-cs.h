
#ifndef _Interaction_Func_Implement_Angle_Harmonic_Both_Cosine_H_
#define _Interaction_Func_Implement_Angle_Harmonic_Both_Cosine_H_

#include "interaction/func/impl/angle/harmonic/parameter/name.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename T>
  void BothAngleHarmonicCosine(const T* csAng,const Unique64Bit* P,T* fc,T* df){
    T angle=arcCos(*csAng);
    T dangle=angle-P[AngHarmonicEqAngle].value<T>();
    T f;
    f=P[AngHarmonicStrength].value<T>()*dangle;
    *df=f+f;
    *fc=f*dangle;
  }

}

#endif

