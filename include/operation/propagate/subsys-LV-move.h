
#ifndef _Subsystem_Propagator_Langevin_VerlocityVerlet_Move_H_
#define _Subsystem_Propagator_Langevin_VerlocityVerlet_Move_H_

#include "data/basic/unique-parameter.h"
#include "data/name/monomer-propagator-langevin-vverlet.h"

namespace std {

  template <typename T>
  void LVMove_BeforeG(subsysPropagator<T>& SP) {
    typedef
    void (*mMoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    for(unsigned int i=0;i<SP.merPg.size;++i)
      reinterpret_cast<mMoveFunc>(SP.merPg[i][LV_MoveBeforeG].ptr)(
          SP.merPg[i],static_cast<Vector<UniqueParameter>&>(SP));
  }

  template <typename T>
  void LVMove_AfterG(subsysPropagator<T>& SP) {
    typedef
    void (*mMoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    for(unsigned int i=0;i<SP.merPg.size;++i) {
      scale(*reinterpret_cast<Vector<T>*>(SP.merPg[i][GVector].ptr),
            *reinterpret_cast<Vector<T>*>(SP.merPg[i][MskVector].ptr));
      reinterpret_cast<mMoveFunc>(SP.merPg[i][LV_MoveBeforeG].ptr)(
          SP.merPg[i],static_cast<Vector<UniqueParameter>&>(SP));
    }
  }

  /*
  template<template<typename,template<typename>class,typename>
           class InteractionType, typename ParameterType, typename T,
           template<typename> class DBuffer, typename GeomType>
  void LVMoveStep(
      InteractionType<T,DBuffer,GeomType>& F,
      Vector<T>* X, Vector<T>* V, Vector<T>* G,
      const Vector<T>* dMask, const ParameterType& pmx,
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
    CalcInteraction(F,X,pmx,G);
    for(unsigned int i=0;i<nunit;++i) scale(G[i],dMask[i]);
    for(unsigned int i=0;i<nunit;++i)
      reinterpret_cast<MoveFunc>(MP[i][LV_MoveAfterG].ptr)(
          X[i],V[i],G[i],dMask[i],PGP,MP[i]);
  }
  */

}

#endif

