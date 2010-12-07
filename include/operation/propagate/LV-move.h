
#ifndef _Propagator_Langevin_VerlocityVerlet_Move_H_
#define _Propagator_Langevin_VerlocityVerlet_Move_H_

#include "data/basic/unique-parameter.h"
#include "data/name/propagator-monomer-langevin-vverlet.h"

namespace std {

  template<template<typename,template<typename>class,typename>
           class InteractionType, typename IdxType, typename T,
           template<typename> class DBuffer, typename GeomType>
  void LVMoveStep(
      InteractionType<T,DBuffer,GeomType>& F,
      Vector<T>* X, Vector<T>* V, Vector<T>* G,
      const Vector<T>* dMask, const IdxType& idx,
      Vector<UniqueParameter>& PGP, Vector<UniqueParameter>* MP,
      const unsigned int& nunit) {
    typedef void (*MoveFunc)(
        Vector<T>&,Vector<T>&,const Vector<T>&,const Vector<T>&,
        const Vector<UniqueParameter>&, const Vector<UniqueParameter>&);
    for(unsigned int i=0;i<nunit;++i)
      reinterpret_cast<MoveFunc>(MP[i][LV_MoveBeforeG].ptr)(
          X[i],V[i],G[i],dMask[i],PGP,MP[i]);
    F.B.renew(X);
    for(unsigned int i=0;i<nunit;++i) copy(G[i],0.);
    CalcInteraction(F,X,idx,G);
    for(unsigned int i=0;i<nunit;++i) scale(G[i],dMask[i]);
    for(unsigned int i=0;i<nunit;++i)
      reinterpret_cast<MoveFunc>(MP[i][LV_MoveAfterG].ptr)(
          X[i],V[i],G[i],dMask[i],PGP,MP[i]);
  }

}

#endif

