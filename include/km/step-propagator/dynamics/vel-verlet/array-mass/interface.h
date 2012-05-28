
#ifndef _Step_Propagator_Dynamics_VelVerlet_ArrayMass_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_ArrayMass_Interface_H_

#include "step-propagator/dynamics/vel-verlet/interface.h"
#include "step-propagator/dynamics/vel-verlet/parameter-name.h"

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

#ifndef _TypePtr_
#define _TypePtr_             AAType
#else
#error "Duplicate _TypePtr_"
#endif

#ifndef _TypeSrc_
#define _TypeSrc_             AType
#else
#error "Duplicate _TypeSrc_"
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

#ifndef _SrcArray_
#define _SrcArray_(U)         (*_PointerArray_(Src,U))
#else
#error "Duplicate _SrcArray_"
#endif

#ifndef _Src2Ptr_Array_
#define _Src2Ptr_Array_(U) \
  if(_PointerArray_(Src,U)!=NULL) { \
    _PointerArray_(Ptr,U)=new AAType; \
    this->_Introduce(_PtrArray_(U),_SrcArray_(U)); \
  }
#else
#error "Duplicate _Src2Ptr_Array_"
#endif

#ifndef _PtrClean_
#define _PtrClean_(U) \
  if(_PointerArray_(Ptr,U)!=NULL) { \
    delete _PointerArray_(Ptr,U); \
    _PointerArray_(Ptr,U)=NULL; \
  }
#else
#error "Duplicate _PtrClean_"
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
#define _PPARAM_(U)           P[Propagator##U]
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
  class StepPropagatorVelVerlet_AMass : public StepPropagatorVelVerlet<T> {

    public:

      typedef StepPropagatorVelVerlet_AMass<T>    Type;
      typedef StepPropagatorVelVerlet<T>  ParentType;
      typedef Array2DNumeric<T>   AType;
      typedef Array<AType>        AAType;

      StepPropagatorVelVerlet_AMass() : ParentType() {}
      virtual ~StepPropagatorVelVerlet_AMass() { Clear(*this); }

      virtual void Init() {
        _Src2Ptr_Array_(Mass)
        _Src2Ptr_Array_(NegHTIM)
        _Src2Ptr_Array_(VelocitySQ)
      }
      virtual void Clean() {
        _PtrClean_(Mass)
        _PtrClean_(NegHTIM)
        _PtrClean_(VelocitySQ)
      }

      virtual void Update1() {  // HTIM
        assert(this->_param.IsValid());
        T hdt=-0.5*_SrcValue_(TimeStep);
        const unsigned int n=_PtrArray_(Mass).Size();
        for(unsigned int i=0;i<n;++i) {
          _PtrArray_(NegHTIM)[i].BlasCopy(_PtrArray_(Mass)[i]);
          _PtrArray_(NegHTIM)[i].Inverse();
          _PtrArray_(NegHTIM)[i].BlasScale(hdt);
        }
      }
      virtual void Update2() {  // VelocitySQ
        assert(this->_param.IsValid());
        assert(this->_V.IsValid());
        const unsigned int n=this->_V.Size();
        for(unsigned int i=0;i<n;++i) {
          _PtrArray_(VelocitySQ)[i].BlasCopy(this->_V[i]);
          _PtrArray_(VelocitySQ)[i].BlasScale(this->_V[i]);
        }
      }
      virtual void Update3() {  // KineticEnergy_Simple
        assert(this->_param.IsValid());
        T d=0;
        const unsigned int n=_PtrArray_(VelocitySQ).Size();
        for(unsigned int i=0;i<n;++i)
          d+=BlasDot(_PtrArray_(Mass)[i],_PtrArray_(VelocitySQ)[i]);
        _ValValue_(KineticEnergy)=0.5*d;
      }

      virtual void Load(Array<Unique64Bit>& P) {
        ParentType::Load(P);
        _LoadPointer_(AType,Mass)
        _LoadPointer_(AType,NegHTIM)
        _LoadPointer_(AType,VelocitySQ)
      }

    private:

      StepPropagatorVelVerlet_AMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerlet_AMass<T>& P) {
    typedef typename StepPropagatorVelVerlet_AMass<T>::ParentType PType;
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

#ifdef _PtrClean_
#undef _PtrClean_
#endif

#ifdef _Src2Ptr_Array_
#undef _Src2Ptr_Array_
#endif

#ifdef _SrcArray_
#undef _SrcArray_
#endif

#ifdef _PtrArray_
#undef _PtrArray_
#endif

#ifdef _PointerArray_
#undef _PointerArray_
#endif

#ifdef _TypeSrc_
#undef _TypeSrc_
#endif

#ifdef _TypePtr_
#undef _TypePtr_
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

