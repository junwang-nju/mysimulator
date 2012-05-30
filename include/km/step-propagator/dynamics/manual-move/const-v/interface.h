
#ifndef _Step_Propagator_Dynamics_ManualMove_ConstV_Interface_H_
#define _Step_Propagator_Dynamics_ManualMove_ConstV_Interface_H_

#include "step-propagator/dynamics/manual-move/interface.h"

namespace mysimulator {

  void VGenerator_ConstV(const Array<Unique64Bit>&,Array<Array2DNumeric<T> >&) {
  }

  template <typename T>
  class StepPropagatorManualConstV : public StepPropagatorManualMove<T> {

    public:

      typedef StepPropagatorManualConstV<T>   Type;
      typedef StepPropagatorManualMove<T>     ParentType;

      StepPropagatorManualConstV() : ParentType() {
        this->VGenerator=VGenerator_ConstV;
      }
      virtual ~StepPropagatorManualConstV() { Clear(*this); }

      virtual void Allocate() { this->_tag=ConstVelocity; }

    private:

      StepPropagatorManualConstV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorManualConstV<T>& P) {
    typedef typename StepPropagatorManualConstV<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

