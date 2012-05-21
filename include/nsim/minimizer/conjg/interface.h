
#ifndef _Minimizer_ConjugateGradient_Interface_H_
#define _Minimizer_ConjugateGradient_Interface_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  struct Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,BT,CT,LMC>
      : public LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC> {

    public:

      typedef Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,BT,CT,LMC>  Type;
      typedef LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC>  ParentType;

      static const unsigned int DefaultMaxSteps;

      Array2D<T> OldMinG;
      T MaxBeta;

      Minimizer() : ParentType(), OldMinG(), MaxBeta(0) {}
      ~Minimizer() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               OldMinG.IsValid();
      }

      void SetMaxBeta() { MaxBeta=5.; }
      template <typename T1> void SetMaxBeta(const T1& B) { MaxBeta=B; }

      int Go(unsigned int MaxSteps=DefaultMaxSteps) {
        assert(IsValid());
        this->GCalcCount=0;
        this->LineSearchCount=0;
        _Load2Mem(*this);
        int fg=0, lfg;
        bool isSteep=true, nextMode;;
        T beta=0;
        T fnorm2,fnorm2;
        fnorm=Norm(this->MemSys->Content.EGData.Gradient);
        if(fnorm<this->GradThreshold)   fg=3;
        else {
          fnorm2=fnorm*fnorm;
        }
        return fg;
      }

    private:

      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  const unsigned int
  Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,BT,CT,LMC>::DefaultMaxSteps=
      1000;

}

#endif

