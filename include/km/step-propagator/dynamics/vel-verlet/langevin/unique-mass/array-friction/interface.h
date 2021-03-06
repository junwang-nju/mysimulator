
#ifndef _Step_Propagator_Dynamics_VelVerlet_Langevin_UMass_AFric_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_Langevin_UMass_AFric_Interface_H_

#include "step-propagator/dynamics/vel-verlet/langevin/unique-mass/interface.h"
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
  class StepPropagatorVelVerletLangevin_UMassAFric
      : public StepPropagatorVelVerletLangevin_UMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_UMassAFric<T> Type;
      typedef StepPropagatorVelVerletLangevin_UMass<T>  ParentType;
      typedef Array2DNumeric<T>   AType;
      typedef Array<AType>        AAType;

      StepPropagatorVelVerletLangevin_UMassAFric() : ParentType() {}
      virtual ~StepPropagatorVelVerletLangevin_UMassAFric() { Clear(*this); }

      virtual void Init() {
        ParentType::Init();
        _Src2Ptr_Array_(Friction)
        _Src2Ptr_Array_(RandSize)
        _Src2Ptr_Array_(FacBf)
        _Src2Ptr_Array_(FacAf)
      }
      virtual void Clean() {
        ParentType::Clean();
        _PtrClean_(Friction)
        _PtrClean_(RandSize)
        _PtrClean_(FacBf)
        _PtrClean_(FacAf)
      }

      virtual void Update5() {
        assert(this->_param.IsValid());
        const unsigned int n=_PtrArray_(Friction).Size();
        for(unsigned int i=0;i<n;++i) {
          _PtrArray_(RandSize)[i].BlasCopy(_PtrArray_(Friction)[i]);
          _PtrArray_(RandSize)[i].BlasScale(
              -2*_PtrValue_(NegHTIM)*_SrcValue_(Temperature));
          _PtrArray_(RandSize)[i].SqRoot();
        }
      }
      virtual void Update6() {
        assert(this->_param.IsValid());
        const unsigned int n=_PtrArray_(Friction).Size();
        for(unsigned int i=0;i<n;++i) {
          _PtrArray_(FacBf)[i].BlasCopy(_PtrArray_(Friction)[i]);
          _PtrArray_(FacBf)[i].BlasScale(_PtrValue_(NegHTIM));
          _PtrArray_(FacAf)[i].BlasCopy(_PtrArray_(FacBf)[i]);
          _PtrArray_(FacBf)[i].BlasShift(1);
          _PtrArray_(FacAf)[i].BlasScale(-1);
          _PtrArray_(FacAf)[i].BlasShift(1);
          _PtrArray_(FacAf)[i].Inverse();
        }
      }

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_G.Size());
        assert(this->_X.Size()==this->_V.Size());
        this->ProduceRandVector();
        const unsigned int n=this->_X.Size();
        for(unsigned int i=0;i<n;++i) {
          this->_V[i].BlasScale(_PtrArray_(FacBf)[i]);
          this->_V[i].BlasShift(this->_G[i],_PtrValue_(NegHTIM));
          this->_V[i].BlasShift(_PtrArray_(RandVector)[i],
                                _PtrArray_(RandSize)[i]);
          this->_X[i].BlasShift(this->_V[i],_SrcValue_(TimeStep));
        }
      }
      virtual void Evolute2() {
        assert(this->_param.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_G.Size()==this->_V.Size());
        this->ProduceRandVector();
        const unsigned int n=this->_V.Size();
        for(unsigned int i=0;i<n;++i) {
          this->_V[i].BlasShift(_PtrArray_(RandVector)[i],
                                _PtrArray_(RandSize)[i]);
          this->_V[i].BlasShift(this->_G[i],_PtrValue_(NegHTIM));
          this->_V[i].BlasScale(_PtrArray_(FacAf)[i]);
        }
      }

      virtual void Load(Array<Unique64Bit>& P) {
        ParentType::Load(P);
        _LoadPointer_(AType,Friction)
        _LoadPointer_(AType,RandSize)
        _LoadPointer_(AType,FacBf)
        _LoadPointer_(AType,FacAf)
      }

    private:

      StepPropagatorVelVerletLangevin_UMassAFric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_UMassAFric<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_UMassAFric<T>::ParentType
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

