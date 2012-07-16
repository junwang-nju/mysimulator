
#ifndef _Step_Propagator_Dynamics_ManualMove_Interface_H_
#define _Step_Propagator_Dynamics_ManualMove_Interface_H_

#include "step-propagator/dynamics/interface.h"

namespace mysimulator {

  template <typename T> class StepPropagatorManualMove;
  template <typename T> void Clear(StepPropagatorManualMove<T>&);

  template <typename T>
  class StepPropagatorManualMove : public StepPropagatorDynamics<T> {

    public:

      typedef StepPropagatorManualMove<T>   Type;
      typedef StepPropagatorDynamics<T>     ParentType;
      typedef void (*VelGeneratorType)(const Array<Unique64Bit>&,
                                       Array<Array2DNumeric<T> >&);
      friend void Clear<T>(StepPropagatorManualMove<T>&);

      StepPropagatorManualMove() : ParentType(), VGenerator(NULL) {}
      virtual ~StepPropagatorManualMove() { Clear(*this); }

      virtual void Init() {}
      virtual void Clean() {}
      virtual void Update() {}
      virtual void Update1() {}
      virtual void Update2() {}
      virtual void Update3() {}
      virtual void Update4() {}
      virtual void Update5() {}
      virtual void Update6() {}
      virtual void Update7() {}

      virtual const T KineticEnergy() const { return 0; }
      virtual unsigned int DegreeFreedom() const { return 0; }

    protected:

      VelGeneratorType VGenerator;

    private:

      StepPropagatorManualMove(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorManualMove<T>& P) {
    P.VGenerator=NULL;
    typedef typename StepPropagatorManualMove<T>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

