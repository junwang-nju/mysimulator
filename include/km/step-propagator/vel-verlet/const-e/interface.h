
#ifndef _Step_Propagator_VelVerlet_ConstE_Interface_H_
#define _Step_Propagator_VelVerlet_ConstE_Interface_H_

#include "step-propagator/name.h"
#include "step-propagator/vel-verlet/const-e/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> PropagatorWithMass>
  class StepPropagatorVelVerletConstE : public PropagatorWithMass<T> {

    public:

      typedef StepPropagatorVelVerletConstE<T,PropagatorWithMass> Type;
      typedef PropagatorWithMass<T> ParentType;

      StepPropagatorVelVerletConstE() : ParentType() {}
      ~StepPropagatorVelVerletConstE() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=VelVerletConstE;
        this->_param.Allocate(VelVerletConstE_NumberParameter);
      }

      virtual void Update5() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Update6() { fprintf(stderr,"Not Implemented!\n"); }

    private:

      StepPropagatorVelVerletConstE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename> PM>
  void Clear(StepPropagatorVelVerletConstE<T,PM>& P) {
    typedef StepPropagatorVelVerletConstE<T,PM>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

