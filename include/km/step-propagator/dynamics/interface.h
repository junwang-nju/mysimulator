
#ifndef _Step_Propagator_Dynamics_Interface_H_
#define _Step_Propagator_Dynamics_Interface_H_

#include "step-propagator/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorDynamics : public StepPropagator<T> {

    public:

      typedef StepPropagatorDynamics<T>   Type;
      typedef StepPropagator<T>     ParentType;

      StepPropagatorDynamics() : ParentType() {}
      virtual ~StepPropagatorDynamics() { Clear(*this); }

    private:

      StepPropagatorDynamics(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorDynamics<T>& P) {
    typedef typename StepPropagatorDynamics<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

