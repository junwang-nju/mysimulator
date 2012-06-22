
#ifndef _Step_Propagator_Dynamics_VelVerlet_ConstE_AMass_Interface_H_
#define _Step_Propagator_Dynamics_VelVerlet_ConstE_AMass_Interface_H_

#include "step-propagator/dynamics/vel-verlet/const-e/interface.h"
#include "step-propagator/dynamics/vel-verlet/array-mass/interface.h"

#ifndef _NAME_
#define _NAME_(DT,U)          VelVerletConstE_##DT##U
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

#ifndef _SrcValue_
#define _SrcValue_(U)         _Value_(Src,U)
#else
#error "Duplicate _SrcValue_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorVelVerletConstE_AMass
      : public StepPropagatorVelVerletConstE<T,StepPropagatorVelVerlet_AMass> {

    public:

      typedef StepPropagatorVelVerletConstE_AMass<T>    Type;
      typedef StepPropagatorVelVerletConstE<T,StepPropagatorVelVerlet_AMass>
              ParentType;
      typedef Array2DNumeric<T> AType;
      typedef Array<AType>      AAType;

      StepPropagatorVelVerletConstE_AMass() : ParentType() {}
      virtual ~StepPropagatorVelVerletConstE_AMass() { Clear(*this); }

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_G.IsValid());
        assert(this->_X.Size()==this->_V.IsValid());
        const unsigned int n=this->_X.Size();
        for(unsigned int i=0;i<n;++i) {
          this->_V[i].BlasShift(this->_G[i],_PtrArray_(NegHTIM)[i]);
          this->_X[i].BlasShift(this->_V[i],_SrcValue_(TimeStep));
        }
      }
      virtual void Evolute2() {
        assert(this->_param.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_G.Size()==this->_V.IsValid());
        const unsigned int n=this->_V.Size();
        for(unsigned int i=0;i<n;++i)
          this->_V[i].BlasShift(this->_G[i],_PtrArray_(NegHTIM)[i]);
      }

    private:

      StepPropagatorVelVerletConstE_AMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletConstE_AMass<T>& P) {
    typedef typename StepPropagatorVelVerletConstE_AMass<T>::ParentType
            PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _SrcValue_
#undef _SrcValue_
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

