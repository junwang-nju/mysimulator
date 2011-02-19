
#ifndef _Interaction_Spheric_Shell_LJ612Cut_H_
#define _Interaction_Spheric_Shell_LJ612Cut_H_

#include "operation/interaction/spheric-shell-base.h"
#include "data/name/external-object-lj612cut.h"
#include "operation/functional/lj612cut.h"

namespace std {

  template <typename T,template <typename> class DBuffer,typename GeomType>
  void EFuncSphericShellLJ612Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL) {
    EFuncSphericShellBase(X,idx,P,B,Geo,Energy,FuncLJ612Cut);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void GFuncSphericShellLJ612Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    GFuncSphericShellBase(X,idx,P,B,Geo,Gradient,DiffLJ612Cut);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void BFuncSphericShellLJ612Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    BFuncSphericShellBase(X,idx,P,B,Geo,Energy,Gradient,BothLJ612Cut);
  }

}

#endif
