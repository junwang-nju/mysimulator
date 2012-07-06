
#ifndef _Propagator_Minimizer_SteepestDescent_Interface_H_
#define _Propagator_Minimizer_SteepestDescent_Interface_H_

#include "propagator/minimizer/interface.h"
#include "propagator/minimizer/steep/parameter-name.h"

namespace mysimulator {

  template <typename T,typename GT,
            template<typename,typename> class LineMinimizer=
                                              PropagatorTrackingLineMinimizer>
  class PropagatorSteepestDescentMinimizer
      : public PropagatorMinimizer<T,GT,LineMinimizer> {

    public:

      typedef PropagatorSteepestDescentMinimizer<T,GT,LineMinimizer> Type;
      typedef PropagatorMinimizer<T,GT,LineMinimizer> ParentType;

      PropagatorSteepestDescentMinimizer() : ParentType() {}
      ~PropagatorSteepestDescentMinimizer() { Clear(*this); }

      virtual void Update() {
        ParentType::Update();
        if(Value<unsigned int>(this->_param[SteepMinimizer_MaxStep])==0)
          Value<unsigned int>(this->_param[SteepMinimizer_MaxStep])=10000;
      }
      virtual void Allocate(const Array<StepPropagatorName>& PN,...) {
        this->_tag=SteepestDescentMinimizer;
        ParentType::Allocate(PN);
        this->_param.Allocate(SteepMinimizer_NumberParameter);
        this->BuildLine();
      }
      virtual unsigned int Evolute(System<T,GT>& S) {
        assert(this->IsValid());
        Value<unsigned int>(this->_param[BaseMin_GCalcCount])=0;
        Value<unsigned int>(this->_param[SteepMinimizer_LineSearchCount])=0;
        T tmd,tmd2;
        unsigned int fg=0, lfg;
        const unsigned int n=
          Value<unsigned int>(this->_param[SteepMinimizer_MaxStep]);
        for(unsigned int i=0;i<n;++i) {
          S.Velocity().BlasCopy(S.Gradient());
          tmd=S.Velocity().BlasNorm();
          if(tmd<Value<T>(this->_param[LineMin_GradThreshold])) { fg=3; break; }
          S.Velocity().BlasScale(-1./tmd);
          this->Proj=-tmd;
          tmd=S.Energy();
          lfg=ParentType::Evolute(S);
          ++Value<unsigned int>(this->_param[SteepMinimizer_LineSearchCount]);
          if(lfg==2) { fg=1; break; }
          else if(lfg==0) { fg=4; break; }
          else {
            tmd2=S.Energy();
            if(2*AbsVal(tmd-tmd2)<=AbsVal(tmd+tmd2)*_RelDelta<T>()) {
              fg=2; break;
            }
          }
        }
        return fg;
      }

    private:

      PropagatorSteepestDescentMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      virtual void IndependentModule() {}

  };

  template <typename T,typename GT,template<typename,typename> class LM>
  void Clear(PropagatorSteepestDescentMinimizer<T,GT,LM>& M) {
    typedef typename PropagatorSteepestDescentMinimizer<T,GT,LM>::ParentType
                     PType;
    Clear(static_cast<PType&>(M));
  }

}

#endif

