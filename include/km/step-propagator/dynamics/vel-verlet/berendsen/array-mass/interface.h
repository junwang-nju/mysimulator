
#ifndef _Step_Propagator_Dynamics_VelVerlet_Berendsen_AMass_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_Berendsen_AMass_Interface_H_

#include "step-propagator/dynamics/vel-verlet/berendsen/interface.h"

#ifndef _NAME_
#define _NAME_(DT,U)          VelVerletBerendsen_##DT##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(DT,U)         this->_param[_NAME_(DT,U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _TypePtr_
#define _TypePtr_             AAType
#else
#error "Duplicate _TypePtr_"
#endif

#ifndef _PointerArray_
#define _PointerArray_(DT,U)  Pointer<_Type##DT##_>(_PARAM_(DT,U))
#else
#error "Duplicate _PointerArray_"
#endif

#ifndef _PtrArray_
#define _PtrArray_(U)         (*_PointerArray_(Ptr,U))
#else
#error "Duplicate _PtrArray_"
#endif

#ifndef _ValValue_
#define _ValValue_(U)         Value<T>(_PARAM_(Val,U))
#else
#error "Duplicate _ValValue_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletBerendsen_AMass
    : public
      StepPropagatorVelVerletBerendsen<T,StepPropagatorVelVerletConstE_AMass> {

    public:

      typedef StepPropagatorVelVerletBerendsen_AMass<T>   Type;
      typedef
      StepPropagatorVelVerletBerendsen<T,StepPropagatorVelVerletConstE_AMass>
      ParentType;
      typedef Array2DNumeric<T> AType;
      typedef Array<AType>      AAType;

      StepPropagatorVelVerletBerendsen_AMass() : ParentType() {}
      virtual ~StepPropagatorVelVerletBerendsen_AMass() { Clear(*this); }

      virtual void Update7() {
        assert(this->_param.IsValid());
        T d=0;
        const unsigned int n=_PtrArray_(VelocitySQ).Size();
        for(unsigned int i=0;i<n;++i)
          d+=BlasDot(_PtrArray_(Mass)[i],_PtrArray_(VelocitySQ)[i]);
        _ValValue_(DualKineticEnergy)=d;
      }

    private:

      StepPropagatorVelVerletBerendsen_AMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletBerendsen_AMass<T>& P) {
    typedef typename StepPropagatorVelVerletBerendsen_AMass<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _ValValue_
#undef _ValValue_
#endif

#ifdef _PtrArray_
#undef _PtrArray_
#endif

#ifdef _PointerArray_
#undef _PointerArray_
#endif

#ifdef _TypePtr_
#undef _TypePtr_
#endif

#ifdef _PARAM_
#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

