
#ifndef _Step_Propagator_VelVerlet_Langevin_AMass_UFric_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_AMass_UFric_Interface_H_

#include "step-propagator/vel-verlet/langevin/array-mass/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_AMassUFric
      : public StepPropagatorVelVerletLangevin_AMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_AMassUFric<T> Type;
      typedef StepPropagatorVelVerletLangevin_AMass<T>  ParentType;

      StepPropagatorVelVerletLangevin_AMassUFric() : ParentType() {}
      ~StepPropagatorVelVerletLangevin_AMassUFric() { Clear(*this); }

    private:

      StepPropagatorVelVerletLangevin_AMassUFric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

