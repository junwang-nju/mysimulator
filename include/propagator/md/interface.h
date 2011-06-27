
#ifndef _Propagator_MolecularDynamics_Interface_H_
#define _Propagator_MolecularDynamics_Interface_H_

#include "propagator/base/interface.h"
#include "interaction/kernel/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class DBuffer, typename GeomType,
            typename IFType, typename IPType>
  struct MDPropagator : public PropagatorBase<T> {

    typedef MDPropagator<T,DBuffer,GeomType,IFType,IPType>  Type;
    typedef PropagatorBase<T>   ParentType;
    typedef void (*RunStepType)(Type&);

    InteractionKernel<IFType,DBuffer,GeomType,T>  IK;
    IPType  Prm;
    RunStepType Step;

    MDPropagator() : ParentType(), IK(), Prm(), Step(NULL) {}
    MDPropagator(const Type&) { Error("Copier of MDPropagator Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MDPropagator Disabled!");
      return *this;
    }
    ~MDPropagator() { clearData(); }

    void clearData() {
      release(IK); release(Prm); Step=NULL;
      static_cast<ParentType*>(this)->clearData();
    }

  };

  template <typename T, template<typename> class DB, typename GT,
            typename IF, typename IP>
  bool IsValid(const MDPropagator<T,DB,GT,IF,IP>& P) {
    return IsValid(static_cast<PropagatorBase<T>&>(P))&&
           IsValid(P.IK)&&IsValid(P.Prm)&&(P.Step!=NULL);
  }

  template <typename T, template<typename> class DB, typename GT,
            typename IF, typename IP>
  void release(MDPropagator<T,DB,GT,IF,IP>& P) { P.clearData(); }

}

#endif

