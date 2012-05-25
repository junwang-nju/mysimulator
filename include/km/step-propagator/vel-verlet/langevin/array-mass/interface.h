
#ifndef _Step_Propagator_VelVerlet_Langevin_AMass_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_AMass_Interface_H_

#include "step-propagator/vel-verlet/langevin/interface.h"
#include "step-propagator/vel-verlet/array-mass/interface.h"

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

#ifndef _SrcValue_
#define _SrcValue_(U)         _Value_(Src,U)
#else
#error "Duplicate _SrcValue_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletLangevin_AMass
      : public StepPropagatorVelVerletLangevin<T,StepPropagatorVelVerlet_AMass>{

    public:

      typedef StepPropagatorVelVerletLangevin_AMass<T>  Type;
      typedef StepPropagatorVelVerletLangevin<T,StepPropagatorVelVerlet_AMass>
              ParentType;
      typedef Array2DNumeric<T>   AType;
      typedef Array<AType>        AAType;

      StepPropagatorVelVerletLangevin_AMass() : ParentType() {}
      ~StepPropagatorVelVerletLangevin_AMass() { Clear(*this); }

      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        _Src2Ptr_Array_(RandSize)
        _Src2Ptr_Array_(FacBf)
        _Src2Ptr_Array_(FacAf)
      }
      virtual void Clean() {
        static_cast<ParentType*>(this)->Clean();
        _PtrClean_(RandSize)
        _PtrClean_(FacBf)
        _PtrClean_(FacAf)
      }

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_G.Size());
        assert(this->_X.Size()==this->_V.Size());
        const unsigned int n=this->_X.Size();
        for(unsigned int i=0;i<n;++i) {
          this->_V[i].BlasScale(_PtrArray_(FacBf));
          this->_V[i].BlasShift(this->_G[i],_PtrArray_(NegHTIM));
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
        const unsigned int n=this->_V.Size();
        for(unsigned int i=0;i<n;++i) {
          this->_V[i].BlasShift(_PtrArray_(RandVector)[i],
                                _PtrArray_(RandSize)[i]);
          this->_V[i].BlasShift(this->_G[i],_PtrArray_(NegHTIM));
          this->_V[i].BlasScale(_PtrArray_(FacAf));
        }
      }

    private:

      StepPropagatorVelVerletLangevin_AMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

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

