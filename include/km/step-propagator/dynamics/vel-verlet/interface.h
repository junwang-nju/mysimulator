
#ifndef _Step_Propagator_Dynamics_VelVerlet_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_Interface_H_

#include "step-propagator/dynamics/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerlet : public StepPropagatorDynamics<T> {

    public:

      typedef StepPropagatorVelVerlet<T>  Type;
      typedef StepPropagatorDynamics<T>   ParentType;

      StepPropagatorVelVerlet() : ParentType() {}
      ~StepPropagatorVelVerlet() { Clear(*this); }

      virtual void Update4() { this->Update2(); this->Update3(); }

      virtual void Evolute3() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Evolute4() { fprintf(stderr,"Not Implemented!\n"); }

    private:

      StepPropagatorVelVerlet(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerlet<T>& P) {
    typedef typename StepPropagatorVelVerlet<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

