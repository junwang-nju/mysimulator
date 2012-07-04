
#ifndef _Step_Propagator_Binder_MinimizerShift_Interface_H_
#define _Step_Propagator_Binder_MinimizerShift_Interface_H_

#include "step-propagator-binder/interface.h"

namespace mysimulator {

  template <typename T,typename GT>
  class StepPropagatorMinimizerShiftBinder : public StepPropagatorBinder<T,GT> {

    public:

      typedef StepPropagatorMinimizerShiftBinder<T,GT>  Type;
      typedef StepPropagatorBinder<T,GT>    ParentType;

      StepPropagatorMinimizerShiftBinder() : ParentType() {}
      virtual ~StepPropagatorMinimizerShiftBinder() { Clear(*this); }

      virtual void Evolute(ArrayNumeric<ArrayNumeric<T> >& X,T& E,
                           Array2DNumeric<T>& G,GroupedInteraction<T,GT>& I,
                           Array<StepPropagator<T>*>& Props) {
        assert(Props.IsValid());
        for(unsigned int i=0;i<Props.Size();++i) {
          assert(Props[i]!=NULL);
          Props[i].Evolute1();
        }
        I.ClearFlag();
        I.Calc(X,E,G);
      }

    private:

      virtual bool _IsWorkable(const StepPropagatorName SPN) const {
        bool fg;
        switch(SPN) {
          case FixPosition:
          case MinimizerLine:
            fg=true;    break;
          default:
            fg=false;   break;
        }
        return fg;
      }

      StepPropagatorMinimizerShiftBinder(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(StepPropagatorMinimizerShiftBinder<T,GT>& B) {
    typedef typename StepPropagatorMinimizerShiftBinder<T,GT>::ParentType
            PType;
    Clear(static_cast<PType&>(B));
  }

}

#endif

