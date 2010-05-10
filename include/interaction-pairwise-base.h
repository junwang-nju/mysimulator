
#ifndef _Interaction_Pairwise_Base_H_
#define _Interaction_Pairwise_Base_H_

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncPairwiseBase(const Vector<double>* Coor, const unsigned int* Idx,
                         const UniqueParameter* Prm,
                         DistEvalMethod& DEval, const GeomType& Geo,
                         double& Energy,
                         void (*efunc)(const double, const UniqueParameter*,
                                       double&)) {
    Evaluate(DEval,Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double dsq=DEval();
    double ee;
    efunc(dsq,Prm,ee);
    Energy+=ee;
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncPairwiseBase(const Vector<double>* Coor, const unsigned int* Idx,
                         const UniqueParameter* Prm,
                         DistEvalMethod& DEval, const GeomType& Geo,
                         Vector<double>* Gradient,
                         void (*gfunc)(const double, const UniqueParameter*,
                                       double&)) {
    Evaluate(DEval,Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double dsq=DEval();
    double ef;
    gfunc(dsq,Prm,ef);
    shift(Gradient[Idx[0]],+ef,DEval.displacementvec);
    shift(Gradient[Idx[1]],-ef,DEval.displacementvec);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncPairwiseBase(const Vector<double>* Coor, const unsigned int* Idx,
                         const UniqueParameter* Prm,
                         DistEvalMethod& DEval, const GeomType& Geo,
                         double& Energy, Vector<double>* Gradient,
                         void (*bfunc)(const double, const UniqueParameter*,
                                       double&, double&)) {
    Evaluate(DEval,Coor[Idx[0]],Coor[Idx[1]],Idx[0],Idx[1],Geo);
    double dsq=DEval();
    double ee,ef;
    bfunc(dsq,Prm,ee,ef);
    Energy+=ee;
    shift(Gradient[Idx[0]],+ef,DEval.displacementvec);
    shift(Gradient[Idx[1]],-ef,DEval.displacementvec);
  }

}

#endif

