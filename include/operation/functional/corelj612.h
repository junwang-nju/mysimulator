
#ifndef _Functiona_CoreLJ612_H_
#define _Functiona_CoreLJ612_H_

#include "operation/parameter/build-param-corelj612.h"

namespace std {

  void FuncCoreLJ612(const double dsq, const UniqueParameter* prm,
                     double& func) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  func=0.;
    else {
      double tmd=prm[CoreLJ612RadiusSQ].d/dsq;
      tmd*=tmd*tmd;
      func=prm[CoreLJ612EnergyDepth].d*(tmd*(tmd-2.)+1.);
    }
  }

  void DiffCoreLJ612(const double dsq, const UniqueParameter* prm,
                     double& diff) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  diff=0.;
    else {
      double ivd2=1./dsq;
      double tmd=prm[CoreLJ612RadiusSQ].d*ivd2;
      tmd*=tmd*tmd;
      diff=prm[CoreLJ612TwlfEnergyDepth].d*tmd*(1.-tmd)*ivd2;
    }
  }

  void BothCoreLJ612(const double dsq, const UniqueParameter* prm,
                     double& func, double& diff) {
    if(dsq>prm[CoreLJ612RadiusSQ].d)  diff=0.;
    else {
      double ivd2=1./dsq;
      double tmd=prm[CoreLJ612RadiusSQ].d*ivd2;
      tmd*=tmd*tmd;
      func=prm[CoreLJ612EnergyDepth].d*(tmd*(tmd-2.)+1.);
      diff=prm[CoreLJ612TwlfEnergyDepth].d*tmd*(1.-tmd)*ivd2;
    }
  }

}

#endif

