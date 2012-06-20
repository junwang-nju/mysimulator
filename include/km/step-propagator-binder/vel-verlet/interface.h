
#ifndef _Step_Propagator_Binder_VelVerlet_Interface_H_
#define _Step_Propagator_Binder_VelVerlet_Interface_H_

#include "step-propagator-binder/interface.h"

namespace mysimulator {

  template <typename T,typename GT>
  class StepPropagatorVelVerletBinder : public StepPropagatorBinder<T,GT> {

    public:

      typedef StepPropagatorVelVerletBinder<T,GT>   Type;
      typedef StepPropagatorBinder<T,GT>  ParentType;

      StepPropagatorVelVerletBinder() : ParentType() {}
      virtual ~StepPropagatorVelVerletBinder() { Clear(*this); }

      virtual void Evolute(ArrayNumeric<ArrayNumeric<T> >& X,
                           Array2DNumeric<T>& G,
                           GroupedInteraction<T,GT>& I,
                           Array<StepPropagator<T>*>& Props) {
        // assuming X,G have been connected with Props
        assert(X.IsValid());
        assert(I.IsValid());
        assert(Props.IsValid());
        for(unsigned int i=0;i<Props.Size();++i) {
          assert(Props[i]!=NULL);
          Props[i]->Evolute1();
        }
        I.ClearFlag();
        I.Calc(X,G);
        for(unsigned int i=0;i<Props.Size();++i) {
          assert(Props[i]!=NULL);
          Props[i]->Evolute2();
        }
      }

    private:

      virtual bool _IsWorkable(const StepPropagatorName SPN) const {
        bool fg;
        switch(SPN) {
          case VelVerletConstE:
          case VelVerletLangevin:
            fg=true;  break;
          default:
            fg=false; break;
        }
        return fg;
      }

      StepPropagatorVelVerletBinder(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(StepPropagatorVelVerletBinder<T,GT>& B) {
    typedef typename StepPropagatorVelVerletBinder<T,GT>::ParentType PType;
    Clear(static_cast<PType&>(B));
  }

}

#endif

