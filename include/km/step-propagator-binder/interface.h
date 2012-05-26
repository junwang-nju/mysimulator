
#ifndef _Step_Propagator_Binder_Interface_H_
#define _Step_Propagator_Binder_Interface_H_

#include "step-propagator/interface.h"
#include "grouped-interaction/interface.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class StepPropagatorBinder {

    public:

      typedef StepPropagatorBinder<T,GeomType>  Type;

      StepPropagatorBinder() {}
      virtual ~StepPropagatorBinder() { Clear(*this); }

      bool IsWorkable(const Array<StepPropagator<T>*>& Props) {
        assert(Props.IsValid());
        for(unsigned int i=0;i<Props.Size();++i) {
          assert(Props[i]!=NULL);
          if(!IsWorkable(Props[i]->_tag))   return false;
        }
        return true;
      }

      virtual void Evolute(ArrayNumeric<ArrayNumeric<T> >& X,
                           ArrayNumeric<ArrayNumeric<T> >& G,
                           GroupedInteraction<T,GeomType>& I,
                           Array<StepPropagator<T>*>& Props)=0;

    private:

      virtual bool IsWorkable(const StepPropagatorName)=0;

      StepPropagatorBinder(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT>
  void Clear(StepPropagatorBinder<T,GT>&) {}

}

#include "step-propagator-binder/vel-verlet/interface.h"

namespace mysimulator {

  template <typename T,typename GT>
  void Introduce(StepPropagatorBinder<T,GT>* B,
                 const Array<StepPropagator<T>*>& Ps) {
    if(B!=NULL) { delete B; B=NULL; }
    static StepPropagatorVelVerletBinder<T,GT> VVerlet;
    if(VVerlet.IsWorkable(Ps))  B=new StepPropagatorVelVerletBinder<T,GT>;
    else fprintf(stderr,"Not Binder Available!\n");
  }

}

#endif

