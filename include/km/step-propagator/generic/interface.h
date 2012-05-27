
#ifndef _Step_Propagator_Generic_Interface_H_
#define _Step_Propagator_Generic_Interface_H_

#include "step-propagator/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorGeneric : public StepPropagator<T> {

    public:

      typedef StepPropagatorGeneric<T>    Type;
      typedef StepPropagator<T>     ParentType;

      StepPropagatorGeneric() : ParentType() {}
      ~StepPropagatorGeneric() { Clear(*this); }

      virtual bool IsDynamics() const { return true; }
      virtual bool IsMinimizer() const { return true; }

    private:

      StepPropagatorGeneric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorGeneric<T>& P) {
    typedef typename StepPropagatorGeneric<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

