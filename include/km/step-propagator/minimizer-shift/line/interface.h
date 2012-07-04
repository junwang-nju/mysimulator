
#ifndef _Step_Propagator_MinimizerShift_Line_Interface_H_
#define _Step_Propagator_MinimizerShift_Line_Interface_H_

#include "step-propagator/minimizer-shift/interface.h"
#include "step-propagator/minimizer-shift/line/parameter-name.h"

#ifndef _NAME_
#define _NAME_(DT,U)          MinimizerShiftLine_##DT##U
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

#ifndef _SrcValue_
#define _SrcValue_(U)         _Value_(Src,U)
#else
#error "Duplicate _SrcValue_"
#endif

namespace mysimulator {

  template <typename T>
  class StepPropagatorMinimizerShiftLine
      : public StepPropagatorMinimizerShift<T> {

    public:

      typedef StepPropagatorMinimizerShiftLine<T>      Type;
      typedef StepPropagatorMinimizerShift<T>    ParentType;

      StepPropagatorMinimizerShiftLine() : ParentType() {}
      virtual ~StepPropagatorMinimizerShiftLine() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=MinimizerShiftLine;
        this->_param.Allocate(MinimizerShiftLine_NumberParameter);
      }

      virtual void Init() {}
      virtual void Clean() {}

      virtual void Update() {}
      virtual void Update1() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Update2() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Update3() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Update4() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Update5() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Update6() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Update7() { fprintf(stderr,"Not Implemented!\n"); }

      virtual void Evolute1() {
        assert(this->_param.IsValid());
        assert(this->_X.IsValid());
        assert(this->_V.IsValid());
        assert(this->_X.Size()==this->_V.Size());
        for(unsigned int i=0;i<this->_X.Size();++i)
          this->_X[i].BlasShift(this->_V[i],_SrcValue_(Step));
      }
      virtual void Evolute2() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Evolute3() { fprintf(stderr,"Not Implemented!\n"); }
      virtual void Evolute4() { fprintf(stderr,"Not Implemented!\n"); }

    private:

      StepPropagatorMinimizerShiftLine(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagatorMinimizerShiftLine<T>& P) {
    typedef typename StepPropagatorMinimizerShiftLine<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#ifdef _SrcValue_
#undef _SrcValue_
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

