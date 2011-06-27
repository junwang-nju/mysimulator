
#ifndef _Propagator_MolecularDynamics_Allocate_H_
#define _Propagator_MolecularDynamics_Allocate_H_

#include "propagator/md/interface.h"
#include "propagator/base/allocate.h"
#include "propagator/move/vverlet/step.h"

namespace mysimulator {

  template <typename T, template<typename> class DB, typename GT,
            typename IF, typename IP>
  void allocate(MDPropagator<T,DB,GT,IF,IP>& P, const PropagatorMoveName& Mv,
                const Vector<PropagatorEnsembleName>& Es,
                const Vector<Vector<PropagatorMonomerName> >& Mn,
                const unsigned int nunit, const unsigned int dim) {
    release(P);
    allocate(static_cast<PropagatorBase<T>&>(P),Mv,Es,Mn,nunit,dim);
    switch(Mv) {
      case VelocityVerlet:
        P.Step=VelVerletStep<T,DB,GT,IF,IP>;
        break;
      default:
        Error("Unknown Propagator Move Type!");
    }
  }

  template <typename T, template<typename> class DB, typename GT,
            typename IF, typename IP>
  void allocate(MDPropagator<T,DB,GT,IF,IP>& P, const PropagatorMoveName& Mv,
                const Vector<PropagatorEnsembleName>& Es,
                const List<PropagatorMonomerName>& Mn,
                const unsigned int nunit, const unsigned int dim) {
    allocate(P,Mv,Es,Mn.infra,nunit,dim);
  }

  template <typename T, template<typename> class DB, typename GT,
            typename IF, typename IP>
  void imprint(MDPropagator<T,DB,GT,IF,IP>& P,
               const MDPropagator<T,DB,GT,IF,IP>& cP) {
    assert(IsValid(cP));
    release(P);
    imprint(static_cast<PropagatorBase<T>&>(P),
            static_cast<const PropagatorBase<T>&>(cP));
    imprint(P.IK,cP.IK);
    imprint(P.Prm,cP.Prm);
    P.Step=cP.Step;
  }

}

#endif

