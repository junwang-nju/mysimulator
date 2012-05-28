
#ifndef _Step_Propagator_MinimizerShift_Interface_H_
#define _Step_Propagator_MinimizerShift_Interface_H_

#include "step-propagator/interface.h"
#include "step-propagator/minimizer-shift/parameter-name.h"

#ifndef _NAME_
#define _NAME_(DT,U)          MinimizerShift_##DT##U
#else
#error "Duplicate _NAME_"
#endif

#ifndef _PARAM_
#define _PARAM_(DT,U)         this->_param[_NAME_(DT,U)]
#else
#error "Duplicate _PARAM_"
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
  class StepPropagatorMinimizerShift : public StepPropagator<T> {

    public:

      typedef StepPropagatorMinimizerShift<T>    Type;
      typedef StepPropagator<T>   ParentType;

      StepPropagatorMinimizerShift() : ParentType() {}
      virtual ~StepPropagatorMinimizerShift() { Clear(*this); }

      virtual bool IsDynamics() const { return false; }
      virtual bool IsMinimizer() const { return true; }

      virtual void Load(Array<Unique64Bit>& P) {
        assert(P.IsValid());
        _LoadPointer_(T,Step)
      }
      virtual const T KineticEnergy() const {
        fprintf(stderr,"Not Available!\n");
        return 0;
      }

    private:

      StepPropagatorMinimizerShift(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorMinimizerShift<T>& P) {
    typedef typename StepPropagatorMinimizerShift<T>::ParentType  PType;
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

#ifdef _PARAM_
#undef _PARAM_
#endif

#ifdef _NAME_
#undef _NAME_
#endif

#endif

