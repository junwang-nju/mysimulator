
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
                           ArrayNumeric<ArrayNumeric<T> >& G,
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
        I.Calc(X,G);
        for(unsigned int i=0;i<Props.Size();++i) {
          assert(Props[i]!=NULL);
          Props[i]->Evolute2();
        }
      }

    private:

      virtual bool IsWorkable(const StepPropagatorName SPN) {
        switch(SPN) {
          case VelVerletConstE:
          case VelVerletLangevin:
            return true;
        }
        return false;
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

