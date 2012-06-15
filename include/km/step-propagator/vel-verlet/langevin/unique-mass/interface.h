
#ifndef _Step_Propagator_VelVerlet_Langevin_UMass_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_UMass_Interface_H_

#include "step-propagator/vel-verlet/langevin/interface.h"
#include "step-propagator/vel-verlet/unique-mass/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_UMass
      : public StepPropagatorVelVerletLangevin<T,StepPropagatorVelVerlet_UMass>{

    public:

      typedef StepPropagatorVelVerletLangevin_UMass<T>    Type;
      typedef StepPropagatorVelVerletLangevin<T,StepPropagatorVelVerlet_UMass>
              ParentType;

      StepPropagatorVelVerletLangevin_UMass() : ParentType() {}
      virtual ~StepPropagatorVelVerletLangevin_UMass() { Clear(*this); }

    private:

      StepPropagatorVelVerletLangevin_UMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_UMass<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_UMass<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

