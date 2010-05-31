
#ifndef _Interaction_Dihedral_Periodic_H_
#define _Interaction_Dihedral_Periodic_H_

#include "interaction-dihedral-base.h"
#include "functional-dihedral-periodic.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void EFuncDihedralPeriodic(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>* tmvec, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, double& Energy) {
    EFuncDihedralBase(Coor,Idx,Prm,tmvec,DEval,Geo,Energy,FuncDihPeriodic);
  }

  template <typename DistEvalMethod, typename GeomType>
  void GFuncDihedralPeriodic(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>* tmvec, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo, Vector<double>* Gradient) {
    GFuncDihedralBase(Coor,Idx,Prm,tmvec,DEval,Geo,Gradient,DiffDihPeriodic);
  }

  template <typename DistEvalMethod, typename GeomType>
  void BFuncDihedralPeriodic(
      const Vector<double>* Coor, const unsigned int* Idx,
      const UniqueParameter* Prm, const unsigned int nIdx,
      Vector<double>* tmvec, const unsigned int,
      DistEvalMethod& DEval, const GeomType& Geo,
      double& Energy, Vector<double>* Gradient) {
    BFuncDihedralBase(Coor,Idx,Prm,tmvec,DEval,Geo,Energy,Gradient,
                      BothDihPeriodic);
  }

}

#endif

