
#ifndef _Step_Propagator_VelVerlet_ConstE_INterface_H_
#define _Step_Propagator_VelVerlet_ConstE_INterface_H_

#include "step-propagator/interface.h"
#include "step-propagator/vel-verlet-const-e/parameter-name.h"

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletConstE : public StepPropagator<T> {

    public:

      typedef StepPropagatorVelVerletConstE<T>    Type;
      typedef StepPropagator<T>   ParentType;

      StepPropagatorVelVerletConstE() : ParentType() {}
      ~StepPropagatorVelVerletConstE() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=VelVerletConstE;
        this->_param.Allocate(VelVerletConstE_NumberParameter);
      }
      virtual void Update4() {
        this->Update2();
        this->Update3();
      }
      virtual void Update5() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Update6() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Evolute3() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Evolute4() { fprintf(stderr,"Not Implemented!\n"); }

    private:

      StepPropagatorVelVerletConstE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletConstE<T>& P) {
    typedef typename StepPropagatorVelVerletConstE<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

