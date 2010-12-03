
#ifndef _Propagator_ConstantE_VelocityVerlet_Move_H_
#define _Propagator_ConstantE_VelocityVerlet_Move_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter.h"
#include "data/name/parameter-propagator-monomer-conste-vverlet.h"

namespace std {

  template <typename InteractionType, typename IdxType, typename T>
  void EVMoveStep(
      InteractionType& F, Vector<T>* X, Vector<T>* V, Vector<T>* G,
      const Vector<T>* dMask, const IdxType& idx,
      const Vector<UniqueParameter>& PGP, Vector<UniqueParameter>* MP,
      const unsigned int nunit) {
    typedef void (*MoveFunc)(Vector<T>&,Vector<T>&,Vector<T>&,const Vector<T>&,
                             const Vector<UniqueParameter>&,
                             const Vector<UniqueParameter>&);
    for(unsigned int i=0;i<nunit;++i)
      reinterpret_cast<MoveFunc>(MP[i][EV_MoveBeforeG].ptr)(
          X[i],V[i],G[i],dMask[i],PGP,MP[i]);
    F.dbuff.renew();////xxxxxxxxxxxxxxxxxxxxxx
    for(unsigned int i=0;i<nunit;++i) copy(G[i],0.);
    CalcInteraction(F,X,idx,G);
    for(unsigned int i=0;i<nunit;++i) scale(G[i],dMask[i]);
    for(unsigned int i=0;i<nunit;++i)
      reinterpret_cast<MoveFunc>(MP[i][EV_MoveAfterG])(
          X[i],V[i],G[i],dMask[i],PGP,MP[i]);
  }

}

#endif

