
#ifndef _Functional_CoreLJ612_H_
#define _Functional_CoreLJ612_H_

#include "vector-base.h"
#include "parameter-name-corelj612.h"

namespace std {

  void FuncCoreLJ612(const double dsq, const VectorBase<double>& Prm,
                     double& func) {
    if(dsq<Prm[CoreLJ612_RadiusSQ]) {
      double tmd=Prm[CoreLJ612_RadiusSQ]/dsq;
      tmd*=tmd*tmd;
      func=Prm[CoreLJ612_Strength]*(tmd*(tmd-2.)+1.);
    } else func=0.;
  }

  void DiffCoreLJ612(const double dsq, const VectorBase<double>& Prm,
                     double& diff) {
    if(dsq<Prm[CoreLJ612_RadiusSQ]) {
      double ivd2=1./dsq;
      double tmd=Prm[CoreLJ612_RadiusSQ]*ivd2;
      tmd*=tmd*tmd;
      diff=Prm[CoreLJ612_TwlfStrength]*tmd*(1.-tmd)*ivd2;
    } else diff=0.;
  }

  void BothCoreLJ612(const double dsq, const VectorBase<double>& Prm,
                     double& func, double& diff) {
    if(dsq<Prm[CoreLJ612_RadiusSQ]) {
      double ivd2=1./dsq;
      double tmd=Prm[CoreLJ612_RadiusSQ]*ivd2;
      tmd*=tmd*tmd;
      func=Prm[CoreLJ612_Strength]*(tmd*(tmd-2.)+1.);
      diff=Prm[CoreLJ612_TwlfStrength]*tmd*(1.-tmd)*ivd2;
    } else func=diff=0.;
  }

}

#endif

