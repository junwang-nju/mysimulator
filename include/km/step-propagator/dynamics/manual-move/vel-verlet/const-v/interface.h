
#ifndef _Step_Propagator_Dynamics_ManualMove_VelVerlet_ConstV_Interface_H_
#define _Step_Propagator_Dynamics_ManualMove_VelVerlet_ConstV_Interface_H_

#include "step-propagator/dynamics/manual-move/vel-verlet/interface.h"
#include "step-propagator/dynamics/manual-move/vel-verlet/const-v/parameter-name.h"

namespace mysimulator {

  template <typename T>
  void VGenerator_VelVerletConstV(
      const Array<Unique64Bit>&,Array<Array2DNumeric<T> >&) {}

  template <typename T>
  class StepPropagatorVelVerletConstV
      : public StepPropagatorManualVelVerlet<T> {

    public:

      typedef StepPropagatorVelVerletConstV<T>      Type;
      typedef StepPropagatorManualVelVerlet<T>      ParentType;

      StepPropagatorVelVerletConstV() : ParentType() {
        this->VGenerator=VGenerator_VelVerletConstV<T>;
      }
      virtual ~StepPropagatorVelVerletConstV() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=VelVerletConstVelocity;
        this->_param.Allocate(VelVerletConstV_NumberParameter);
      }

    private:

      StepPropagatorVelVerletConstV(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletConstV<T>& P) {
    typedef typename StepPropagatorVelVerletConstV<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

