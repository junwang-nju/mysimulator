
#ifndef _Interaction_Spheric_Shell_CoreLJ612_H_
#define _Interaction_Spheric_Shell_CoreLJ612_H_

#include "operation/interaction/spheric-shell-base.h"
#include "data/name/external-object-corelj612.h"
#include "operation/functional/corelj612.h"

namespace std {

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void EFuncSphericShellCoreLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncSphericShellBase(X,idx,P,B,Geo,Energy,FuncCoreLJ612);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void GFuncSphericShellCoreLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncSphericShellBase(X,idx,P,B,Geo,Gradient,DiffCoreLJ612);
  }

  template <typename T, template<typename> class DBuffer,typename GeomType>
  void BFuncSphericShellCoreLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncSphericShellBase(X,idx,P,B,Geo,Energy,Gradient,BothCoreLJ612);
  }

}

#endif

