
#ifndef _Step_Propagator_Dynamics_ManualMove_VelVerlet_Interface_H_
#define _Step_Propagator_Dynamics_ManualMove_VelVerlet_Interface_H_

#include "step-propagator/dynamics/manual-move/interface.h"
#include "step-propagator/dynamics/manual-move/vel-verlet/parameter-name.h"
#include "propagator/molecular-dynamics/parameter-name.h"

#ifndef _NAME_
#define _NAME_(DT,U)    ManualVelVerlet_##DT##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(DT,U)   this->_param[_NAME_(DT,U)]
#else
#error "Duplicate _PARAM_"
#endif

#ifndef _Pointer_
#define _Pointer_(DT,U) Pointer<T>(_PARAM_(DT,U))
#else
#error "Duplicate _Pointer_"
#endif

#ifndef _Value_
#define _Value_(DT,U)   (*_Pointer_(DT,U))
#else
#error "Duplicate _Value_"
#endif

#ifndef _SrcValue_
#define _SrcValue_(U)   _Value_(Src,U)
#else
#error "Duplicate _SrcValue_"
#endif

#ifndef _SrcPointer_
#define _SrcPointer_(RT,U)  Pointer<RT>(_PARAM_(Src,U))
#else
#error "Duplicate _SrcPointer_"
#endif

#ifndef _PPARAM_
#define _PPARAM_(U)     P[PropagatorMD_##U]
#else
#error "Duplicate _PPARAM_"
#endif

#define _PPointer_
#define _PPointer_(RT,U)  Pointer<RT>(_PPARAM_(U))
#else
#error "Duplicate _PPointer_"
#endif

#ifndef _LoadPointer_
#define _LoadPointer_(RT,U) \
  if(_PPointer_(RT,U)==NULL) _PPointer_(RT,U)=new RT; \
  _SrcPointer_(RT,U)=_PPointer_(RT,U);
#else
#error "Duplicate _LoadPointer_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorManualVelVerlet : public StepPropagatorManualMove<T> {

    public:

      typedef StepPropagatorManualVelVerlet<T>  Type;
      typedef StepPropagatorManualMove<T>       ParentType;

      StepPropagatorManualVelVerlet() : ParentType() {}
      virtual ~StepPropagatorManualVelVerlet() { Clear(*this); }

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_V.Size());
        assert(VGenerator!=NULL);
        VGenerator(this->_param,this->_V);
        const unsigned int n=this->_X.Size();
        for(unsigned int i=0;i<n;++i)
          this->_X[i].BlasShift(this->_V[i],_SrcValue_(TimeStep));
      }
      virtual void Evolute2() {
        assert(this->_param.IsValid());
        assert(this->_V.IsValid());
        assert(VGenerator!=NULL);
        VGenerator(this->_param,this->_V);
      }
      virtual void Evolute3() {}
      virtual void Evolute4() {}

      virtual void Load(Array<Unique64Bit>& P) {
        assert(P.IsValid());
        _LoadPointer_(T,TimeStep)
      }

    private:

      StepPropagatorManualVelVerlet(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorManualVelVerlet<T>& P) {
    typedef typename StepPropagatorManualVelVerlet<T>::ParentType PType;
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

#ifdef _SrcValue_
#undef _SrcValue_
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

