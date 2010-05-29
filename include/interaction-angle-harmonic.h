
#ifndef _Interaction_Angle_Harmonic_H_
#define _Interaction_Angle_Harmonic_H_

#include "interaction-angle-base.h"
#include "functional-angle-harmonic.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncAngleHarmonic(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>*, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncAngleBase(Coor,Idx,Prm,DEval,Geo,Energy,FuncAngleHarmonic);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncAngleHarmonic(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>* tmvec, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncAngleBase(Coor,Idx,Prm,tmvec,DEval,Geo,Gradient,DiffAngleHarmonic);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncAngleHarmonic(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>* tmvec, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncAngleBase(Coor,Idx,Prm,tmvec,DEval,Geo,Energy,Gradient,
                   BothAngleHarmonic);
  }

}

#endif
