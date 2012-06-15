
#ifndef _Step_Propagator_VelVerlet_Langevin_Interface_H_
#define _Step_Propagator_VelVerlet_Langevin_Interface_H_

#include "step-propagator/name.h"
#include "step-propagator/vel-verlet/langevin/parameter-name.h"

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

namespace mysimulator {

  template <typename T,template<typename> class PropagatorWithMass>
  class StepPropagatorVelVerletLangevin : public PropagatorWithMass<T> {

    public:

      typedef StepPropagatorVelVerletLangevin<T,PropagatorWithMass> Type;
      typedef PropagatorWithMass<T>   ParentType;
      typedef Array2DNumeric<T>   AType;
      typedef Array<AType>        AAType;

      StepPropagatorVelVerletLangevin() : ParentType() {}
      virtual ~StepPropagatorVelVerletLangevin() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=VelVerletLangevin;
        this->_param.Allocate(VelVerletLangevin_NumberParameter);
      }
      virtual void Init() {
        static_cast<ParentType*>(this)->Init();
        _Src2Ptr_Array_(RandVector)
      }
      virtual void Clean() {
        static_cast<ParentType*>(this)->Clean();
        _PtrClean_(RandVector)
      }

    private:

      StepPropagatorVelVerletLangevin(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename> class PM>
  void Clear(StepPropagatorVelVerletLangevin<T,PM>& P) {
    typedef typename StepPropagatorVelVerletLangevin<T,PM>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

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

#ifdef _PARAM_
#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

