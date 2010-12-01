
#ifndef _Interaction_Dihedral_Periodic_H_
#define _Interaction_Dihedral_Periodic_H_

#include "operation/interaction/dihedral-base.h"
#include "operation/functional/dihedral-periodic.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void EFuncDihPeriodic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    EFuncDihedralBase(X,idx,P,B,Geo,Energy,tmvec,FuncDihPeriodic);
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void GFuncDihPeriodic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    GFuncDihedralBase(X,idx,P,B,Geo,Gradient,tmvec,DiffDihPeriodic);
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void BFuncDihPeriodic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    BFuncDihedralBase(X,idx,P,B,Geo,Energy,Gradient,tmvec,BothDihPeriodic);
  }

}

#endif
