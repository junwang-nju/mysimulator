
#ifndef _Interaction_Core_Expanded_Base_H_
#define _Interaction_Core_Expanded_Base_H_

#include "vector.h"
#include "unique-parameter.h"
#include "parameter-name-core-expand-base.h"
#include <cmath>

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncCoreExpandBase(const Vector<double>* Coor, const unsigned int* Idx,
                           const UniqueParameter* Prm,
                           DistEvalMethod& DEval, const GeomType& Geo,
                           double& Energy,
                           void (*efunc)(const double,const UniqueParameter*,
                                         double&)) {
    Evaluate(DEval,Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double cdsq=DEval();
    double cd=sqrt(cdsq);
    double d=cd-Prm[CoreExpCoreRadius].d;
    assert(d>=0);
    double dsq=d*d;
    double ee;
    efunc(dsq,Prm+CoreExpBaseNumberParameter,ee);
    Energy+=ee;
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncCoreExpandBase(const Vector<double>* Coor, const unsigned int* Idx,
                           const UniqueParameter* Prm,
                           DistEvalMethod& DEval, const GeomType& Geo,
                           Vector<double>* Gradient,
                           void (*gfunc)(const double,const UniqueParameter*,
                                         double&)) {
    Evaluate(DEval,Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double cdsq=DEval();
    double cd=sqrt(cdsq);
    double d=cd-Prm[CoreExpCoreRadius].d;
    assert(d>=0);
    double dsq=d*d;
    double ef;
    gfunc(dsq,Prm+CoreExpBaseNumberParameter,ef);
    ef*=d/cd;
    shift(Gradient[Idx[0]],+ef,DEval.displacementvec);
    shift(Gradient[Idx[1]],-ef,DEval.displacementvec);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncCoreExpandBase(const Vector<double>* Coor, const unsigned int* Idx,
                           const UniqueParameter* Prm,
                           DistEvalMethod& DEval, const GeomType& Geo,
                           double& Energy, Vector<double>* Gradient,
                           void (*bfunc)(const double,const UniqueParameter*,
                                         double&,double&)) {
    Evaluate(DEval,Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double cdsq=DEval();
    double cd=sqrt(cdsq);
    double d=cd-Prm[CoreExpCoreRadius].d;
    assert(d>=0);
    double dsq=d*d;
    double ee,ef;
    bfunc(dsq,Prm+CoreExpBaseNumberParameter,ee,ef);
    Energy+=ee;
    ef*=d/cd;
    shift(Gradient[Idx[0]],+ef,DEval.displacementvec);
    shift(Gradient[Idx[1]],-ef,DEval.displacementvec);
  }

}

#endif

