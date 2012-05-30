
#ifndef _Step_Propagator_Dynamics_VelVerlet_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_Interface_H_

#include "step-propagator/dynamics/interface.h"
#include "propagator/molecular-dynamics/parameter-name.h"

#ifndef _NAME_
#define _NAME_(DT,U)          VelVerlet_##DT##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(DT,U)         this->_param[_NAME_(DT,U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _SrcPointer_
#define _SrcPointer_(RT,U)    Pointer<RT>(_PARAM_(Src,U))
#else
#error "Duplicate _SrcPointer_"
#endif

#ifndef _PPARAM_
#define _PPARAM_(U)           P[PropagatorMD_##U]
#else
#error "Duplicate _PPARAM_"
#endif

#ifndef _PPointer_
#define _PPointer_(RT,U)       Pointer<RT>(_PPARAM_(U))
#else
#error "Duplicate _PPointer_"
#endif

#ifndef _LoadPointer_
#define _LoadPointer_(RT,U)  \
  if(_PPointer_(RT,U)==NULL)  _PPointer_(RT,U)=new RT; \
  _SrcPointer_(RT,U)=_PPointer_(RT,U);
#else
#error "Duplicate _LoadPointer_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerlet : public StepPropagatorDynamics<T> {

    public:

      typedef StepPropagatorVelVerlet<T>  Type;
      typedef StepPropagatorDynamics<T>   ParentType;

      StepPropagatorVelVerlet() : ParentType() {}
      virtual ~StepPropagatorVelVerlet() { Clear(*this); }

      virtual void Update4() { this->Update2(); this->Update3(); }

      virtual void Evolute3() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Evolute4() { fprintf(stderr,"Not Implemented!\n"); }

      virtual void Load(Array<Unique64Bit>& P) {
        assert(P.IsValid());
        _LoadPointer_(T,TimeStep)
      }

    private:

      StepPropagatorVelVerlet(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerlet<T>& P) {
    typedef typename StepPropagatorVelVerlet<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _LoadPointer_
#undef _LoadPointer_
#endif

#ifdef _PPointer_
#undef _PPointer_
#endif

#ifdef _PPARAM_
#undef _PPARAM_
#endif

#ifdef _SrcPointer_
#undef _SrcPointer_
#endif

#ifdef _PARAM_
#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

