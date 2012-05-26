
#ifndef _Step_Propagator_VelVerlet_Langevin_UMass_UFric_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_UMass_UFric_Interface_H_

#include "step-propagator/vel-verlet/langevin/unique-mass/interface.h"

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

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_UMassUFric
      : public StepPropagatorVelVerletLangevin_UMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin_UMassUFric<T>   Type;
      typedef StepPropagatorVelVerletLangevin_UMass<T>  ParentType;
      typedef Array2DNumeric<T>   AType;
      typedef Array<AType>        AAType;

      StepPropagatorVelVerletLangevin_UMassUFric() : ParentType() {}
      virtual ~StepPropagatorVelVerletLangevin_UMassUFric() { Clear(*this); }

      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        _Src2Ptr_Pointer_(Friction)
        _Src2Ptr_Pointer_(RandSize)
        _Src2Ptr_Pointer_(FacBf)
        _Src2Ptr_Pointer_(FacAf)
      }
      virtual void Update5() {  // RandSize
        assert(this->_param.IsValid());
        // Work after Update1
        _PtrValue_(RandSize)=
          __SqRoot(-2*_PtrValue_(NegHTIM)*_SrcValue_(Temperature)*
                   _PtrValue_(Friction));
      }
      virtual void Update6() {
        assert(this->_param.IsValid());
        T d=_PtrValue_(NegHTIM)*_PtrValue_(Friction);
        _PtrValue_(FacBf)=1.+d;
        _PtrValue_(FacAf)=1./(1.-d);
      }

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_V.Size());
        assert(this->_X.Size()==this->_G.Size());
        this->ProduceRandVector();
        const unsigned int n=this->_X.Size();
        for(unsigned int i=0;i<n;++i) {
          this->_V[i].BlasScale(_PtrValue_(FacBf));
          this->_V[i].BlasShift(this->_G[i],_PtrValue_(NegHTIM));
          this->_V[i].BlasShift(_PtrArray_(RandVector)[i],_PtrValue_(RandSize));
          this->_X[i].BlasShift(this->_V[i],_SrcValue_(TimeStep));
        }
      }
      virtual void Evolute2() {
        assert(this->_param.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_V.Size()==this->_G.Size());
        this->ProduceRandVector();
        const unsigned int n=this->_V.Size();
        for(unsigned int i=0;i<n;++i) {
          this->_V[i].BlasShift(_PtrArray_(RandVector)[i],_PtrValue_(RandSize));
          this->_V[i].BlasShift(this->_G[i],_PtrValue_(NegHTIM));
          this->_V[i].BlasScale(_PtrValue_(FacAf));
        }
      }

    private:

      StepPropagatorVelVerletLangevin_UMassUFric(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletLangevin_UMassUFric<T>& P) {
    typedef typename StepPropagatorVelVerletLangevin_UMassUFric<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

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

