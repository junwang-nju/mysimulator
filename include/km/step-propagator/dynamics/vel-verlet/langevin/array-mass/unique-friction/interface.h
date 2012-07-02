
#ifndef _Step_Propagator_Dynamics_VelVerlet_Langevin_AMass_UFric_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_Langevin_AMass_UFric_Interface_H_

#include "step-propagator/dynamics/vel-verlet/langevin/array-mass/interface.h"
#include "propagator/molecular-dynamics/parameter-name.h"

#ifndef _NAME_
#define _NAME_(DT,U)          VelVerletLangevin_##DT##U
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
  class StepPropagatorVelVerletLangevin_AMassUFric
      : public StepPropagatorVelVerletLangevin_AMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_AMassUFric<T> Type;
      typedef StepPropagatorVelVerletLangevin_AMass<T>  ParentType;
      typedef Array2DNumeric<T>   AType;
      typedef Array<AType>    AAType;

      StepPropagatorVelVerletLangevin_AMassUFric() : ParentType() {}
      virtual ~StepPropagatorVelVerletLangevin_AMassUFric() { Clear(*this); }

      virtual void Init() {
        ParentType::Init();
        _Src2Ptr_Pointer_(Friction)
      }

      virtual void Update5() {  // RandSize
        assert(this->_param.IsValid());
        const unsigned int n=_PtrArray_(Mass).Size();
        for(unsigned int i=0;i<n;++i) {
          _PtrArray_(RandSize)[i].BlasCopy(_PtrArray_(NegHTIM)[i]);
          _PtrArray_(RandSize)[i].BlasScale(
              -2*_SrcValue_(Temperature)*_PtrValue_(Friction));
          _PtrArray_(RandSize)[i].SqRoot();
        }
      }
      virtual void Update6() {
        assert(this->_param.IsValid());
        const unsigned int n=_PtrArray_(Mass).Size();
        for(unsigned int i=0;i<n;++i) {
          _PtrArray_(FacBf)[i].BlasCopy(_PtrArray_(NegHTIM)[i]);
          _PtrArray_(FacBf)[i].BlasScale(_PtrValue_(Friction));
          _PtrArray_(FacAf)[i].BlasCopy(_PtrArray_(FacBf)[i]);
          _PtrArray_(FacBf)[i].BlasShift(1);
          _PtrArray_(FacAf)[i].BlasScale(-1);
          _PtrArray_(FacAf)[i].BlasShift(1);
          _PtrArray_(FacAf)[i].Inverse();
        }
      }

      virtual void Load(Array<Unique64Bit>& P) {
        ParentType::Load(P);
        _LoadPointer_(T,Friction)
      }

    private:

      StepPropagatorVelVerletLangevin_AMassUFric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_AMassUFric<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_AMassUFric<T>::ParentType
            PType;
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

#ifdef _PtrValue_
#undef _PtrValue_
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

