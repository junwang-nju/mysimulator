
#ifndef _Step_Propagator_Dynamics_VelVerlet_Berendsen_UMass_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_Berendsen_UMass_Interface_H_

#include "step-propagator/dynamics/vel-verlet/berendsen/interface.h"
#include "step-propagator/dynamics/vel-verlet/const-e/unique-mass/interface.h"

#ifndef _NAME_
#define _NAME_(DT,U)        VelVerletBerendsen_##DT##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(DT,U)       this->_param[_NAME_(DT,U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _Pointer_
#define _Pointer_(DT,U)     Pointer<T>(_PARAM_(DT,U))
#else
#error "Duplicate _Pointer_"
#endif

#ifndef _Value_
#define _Value_(DT,U)       (*_Pointer_(DT,U))
#else
#error "Duplicate _Value_"
#endif

#ifndef _PtrValue_
#define _PtrValue_(U)       _Value_(Ptr,U)
#else
#error "Duplicate _PtrValue_"
#endif

#ifndef _ValValue_
#define _ValValue_(U)       Value<T>(_PARAM_(Val,U))
#else
#error "Duplicate _ValValue_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletBerendsen_UMass
    : public
      StepPropagatorVelVerletBerendsen<T,StepPropagatorVelVerletConstE_UMass> {

    public:

      typedef StepPropagatorVelVerletBerendsen_UMass<T>   Type;
      typedef
      StepPropagatorVelVerletBerendsen<T,StepPropagatorVelVerletConstE_UMass>
      ParentType;

      StepPropagatorVelVerletBerendsen_UMass() : ParentType() {}
      ~StepPropagatorVelVerletBerendsen_UMass() { Clear(*this); }

      virtual void Update7() {
        assert(this->_param.IsValid());
        _ValValue_(DualKineticEnergy)=_PtrValue_(Mass)*_PtrValue_(VelocitySQ);
      }

    private:

      StepPropagatorVelVerletBerendsen_UMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletBerendsen_UMass<T>& P) {
    typedef typename StepPropagatorVelVerletBerendsen_UMass<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _ValValue_
#undef _ValValue_
#endif

#ifdef _PtrValue_
#undef _PtrValue_
#endif

#ifdef _Value_
#undef _Value_
#endif

#ifdef _Pointer_
#undef _Pointer_
#endif

#ifdef _PARAM_
#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

