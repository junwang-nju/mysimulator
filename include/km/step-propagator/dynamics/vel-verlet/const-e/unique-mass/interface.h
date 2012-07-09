
#ifndef _Step_Propagator_Dynamics_VelVerlet_ConstE_UMass_H_
#define _Step_Propagator_Dynamics_VelVerlet_ConstE_UMass_H_

#include "step-propagator/dynamics/vel-verlet/const-e/interface.h"
#include "step-propagator/dynamics/vel-verlet/unique-mass/interface.h"

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
  class StepPropagatorVelVerletConstE_UMass
      : public StepPropagatorVelVerletConstE<T,StepPropagatorVelVerlet_UMass> {

    public:

      typedef StepPropagatorVelVerletConstE_UMass<T>  Type;
      typedef StepPropagatorVelVerletConstE<T,StepPropagatorVelVerlet_UMass>
              ParentType;

      StepPropagatorVelVerletConstE_UMass() : ParentType() {}
      virtual ~StepPropagatorVelVerletConstE_UMass() { Clear(*this); }

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_G.Size());
        assert(this->_X.Size()==this->_V.Size());
        const unsigned int n=this->_X.Size();
        for(unsigned int i=0;i<n;++i) {
          this->_V[i].BlasShift(this->_G[i],_PtrValue_(NegHTIM));
          this->_X[i].BlasShift(this->_V[i],_SrcValue_(TimeStep));
        }
      }
      virtual void Evolute2() {
        assert(this->_param.IsValid());
        assert(this->_G.IsValid());
        assert(this->_V.IsValid());
        assert(this->_V.Size()==this->_G.Size());
        const unsigned int n=this->_V.Size();
        for(unsigned int i=0;i<n;++i)
          this->_V[i].BlasShift(this->_G[i],_PtrValue_(NegHTIM));
      }

    private:

      StepPropagatorVelVerletConstE_UMass(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorVelVerletConstE_UMass<T>& P) {
    typedef typename StepPropagatorVelVerletConstE_UMass<T>::ParentType
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

