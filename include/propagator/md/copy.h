
#ifndef _Propagator_MolecularDynamics_Copy_H_
#define _Propagator_MolecularDynamics_Copy_H_

#include "propagator/md/interface.h"
#include "propagator/base/copy.h"
#include "interaction/kernel/copy.h"

namespace mysimulator {

  template <typename T, template<typename> class DB, typename GT,
            typename IF, typename IP>
  void copy(MDPropagator<T,DB,GT,IF,IP>& P,
            const MDPropagator<T,DB,GT,IF,IP>& cP) {
    assert(IsValid(P)&&IsValid(cP));
    copy(static_cast<PropagatorBase<T>&>(P),
         static_cast<const PropagatorBase<T>&>(cP));
    copy(P.IK,cP.IK);
    copy(P.Prm,cP.Prm);
  }

}

#endif

