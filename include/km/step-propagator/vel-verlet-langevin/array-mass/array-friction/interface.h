
#ifndef _Step_Propagator_VelVerlet_Langevin_AMass_AFric_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_AMass_AFric_Interface_H_

#include "step-propagator/vel-verlet-langevin/array-mass/interface.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_AMassAFric
      : public StepPropagatorVelVerletLangevin_AMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_AMassAFric<T> Type;
      typedef StepPropagatorVelVerletLangevin_AMass<T>  ParentType;

      StepPropagatorVelVerletLangevin_AMassAFric() : ParentType() {}
      ~StepPropagatorVelVerletLangevin_AMassAFric() { Clear(*this); }

      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        assert(_SrcArray_(Friction));
      }

    private:

      StepPropagatorVelVerletLangevin_AMassAFric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_AMassAFric<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_AMassAFric<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

