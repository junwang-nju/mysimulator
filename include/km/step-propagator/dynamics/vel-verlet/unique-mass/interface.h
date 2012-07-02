
#ifndef _Step_Propagator_Dynamics_VelVerlet_UMass_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_UMass_Interface_H_

#include "step-propagator/dynamics/vel-verlet/interface.h"
#include "step-propagator/dynamics/vel-verlet/parameter-name.h"
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

#ifndef _Pointer_
#define _Pointer_(DT,U)       Pointer<T>(_PARAM_(DT,U))
#else
#error "Duplicate _Pointer_"
#endif

#ifndef _Value_
#define _Value_(DT,U)         (*_Pointer_(DT,U))
#else
#error "Duplicate _Value_"
#endif

#ifndef _Src2Ptr_Pointer_
#define _Src2Ptr_Pointer_(U)  _Pointer_(Ptr,U)=_Pointer_(Src,U);
#else
#error "Duplicate _Src2Ptr_Pointer_"
#endif

#ifndef _PtrValue_
#define _PtrValue_(U)         _Value_(Ptr,U)
#else
#error "Duplicate _PtrValue_"
#endif

#ifndef _SrcValue_
#define _SrcValue_(U)         _Value_(Src,U)
#else
#error "Duplicate _SrcValue_"
#endif

#ifndef _ValValue_
#define _ValValue_(U)         Value<T>(_PARAM_(Val,U))
#else
#error "Duplicate _ValValue_"
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
  class StepPropagatorVelVerlet_UMass : public StepPropagatorVelVerlet<T> {

    public:

      typedef StepPropagatorVelVerlet_UMass<T> Type;
      typedef StepPropagatorVelVerlet<T>  ParentType;

      StepPropagatorVelVerlet_UMass() : ParentType() {}
      virtual ~StepPropagatorVelVerlet_UMass() { Clear(*this); }

      virtual void Init() {
        _Src2Ptr_Pointer_(Mass)
        _Src2Ptr_Pointer_(NegHTIM)
        _Src2Ptr_Pointer_(VelocitySQ)
      }
      virtual void Clean() {}

      virtual void Update1() {  // HTIM
        assert(this->_param.IsValid());
        _PtrValue_(NegHTIM)=-0.5*_SrcValue_(TimeStep)/_PtrValue_(Mass);
      }
      virtual void Update2() {  // VelocitySQ
        assert(this->_V.IsValid());
        assert(this->_param.IsValid());
        T d=0;
        const unsigned int n=this->_V.Size();
        for(unsigned int i=0;i<n;++i) d+=this->_V[i].BlasNormSQ();
        _PtrValue_(VelocitySQ)=d;
      }
      virtual void Update3() {
        assert(this->_param.IsValid());
        _ValValue_(KineticEnergy)=0.5*_PtrValue_(Mass)*_PtrValue_(VelocitySQ);
      }
      virtual void Load(Array<Unique64Bit>& P) {
        ParentType::Load(P);
        _LoadPointer_(T,Mass)
        _LoadPointer_(T,NegHTIM)
        _LoadPointer_(T,VelocitySQ)
      }

    private:

      StepPropagatorVelVerlet_UMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerlet_UMass<T>& P) {
    typedef typename StepPropagatorVelVerlet_UMass<T>::ParentType  PType;
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

#ifdef _ValValue_
#undef _ValValue_
#endif

#ifdef _SrcValue_
#undef _SrcValue_
#endif

#ifdef _PtrValue_
#undef _PtrValue_
#endif

#ifdef _Src2Ptr_Pointer_
#undef _Src2Ptr_Pointer_
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

