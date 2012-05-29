
#ifndef _Propagator_Minimizer_ConjugateGradient_Interface_H_
#define _Propagator_Minimizer_ConjugateGradient_Interface_H_

#include "propagator/minimizer/interface.h"
#include "propagator/minimizer/conjg/parameter-name.h"

namespace mysimulator {

  template <typename T,typename GT,template<typename,typename> class LM>
  class PropagatorConjugateGradientMinimizer;
  template <typename T,typename GT,template<typename,typename> class LM>
  void Clear(PropagatorConjugateGradientMinimizer<T,GT,LM>& M);

  template <typename T,typename GT,
            template<typename,typename> class LineMinimizer=
                                              PropagatorTrackingLineMinimizer>
  class PropagatorConjugateGradientMinimizer
      : public PropagatorMinimizer<T,GT,LineMinimizer> {

    public:

      typedef PropagatorConjugateGradientMinimizer<T,GT,LineMinimizer>  Type;
      typedef PropagatorMinimizer<T,GT,LineMinimizer> ParentType;
      friend void Clear<T,GT,LineMinimizer>(Type&);

      PropagatorConjugateGradientMinimizer() : ParentType(), _OldG() {}
      ~PropagatorConjugateGradientMinimizer() { Clear(*this); }

      virtual bool IsValid() const {
        return ParentType::IsValid()&&_OldG.IsValid();
      }
      virtual void IntroduceSystem(System<T,GT>& S) {
        ParentType::IntroduceSystem(S);
        _OldG.Imprint(S.Location());
      }
      virtual void DetachSystem() {
        ParentType::DetachSystem();
        Clear(_OldG);
      }

      virtual void Update() {
        ParentType::Update();
        if(Value<unsigned int>(this->_param[ConjgMinimizer_MaxStep])==0)
          Value<unsigned int>(this->_param[ConjgMinimizer_MaxStep])=1000;
        if(Value<T>(this->_param[ConjgMinimizer_MaxBeta])<1e-8)
          Value<T>(this->_param[ConjgMinimizer_MaxBeta])=5.;
      }
      virtual void Allocate(const Array<StepPropagatorName>& PN,...) {
        ParentType::Allocate(PN);
        this->_tag=ConjugateGradientMinimizer;
        this->_param.Allocate(ConjgMinimizer_NumberParameter);
        ParentType::BuildLine();
      }
      virtual unsigned int Evolute(System<T,GT>& S) {
        assert(IsValid());
        Value<unsigned int>(this->_param[BaseMin_GCalcCount])=0;
        Value<unsigned int>(this->_param[ConjgMinimizer_LineSearchCount])=0;
        unsigned int fg=0,lfg;
        bool isSteep=true, nextMode;
        T beta,fnorm,fnorm2;
        beta=0;
        fnorm=S.Gradient().BlasNorm();
        if(fnorm<Value<T>(this->_param[LineMin_GradThreshold])) fg=3;
        else {
          fnorm2=fnorm*fnorm;
          T tmd,tmd2,oldfnorm2,dnorm;
          oldfnorm2=1.;
          dnorm=0.;
          const unsigned int n=
            Value<unsigned int>(this->_param[ConjgMinimizer_MaxStep]);
          const T maxBeta=Value<T>(this->_param[ConjgMinimizer_MaxBeta]);
          const T gTH=Value<T>(this->_param[LineMin_GradThreshold]);
          for(unsigned int i=0;i<n;++i) {
            if(!isSteep) {
              tmd=BlasDot(S.Gradient(),_OldG);
              beta=(fnorm2-tmd)/oldfnorm2;
              isSteep=(AbsVal(beta)>maxBeta);
            }
            if(!isSteep) {
              tmd=beta*dnorm;
              S.Velocity().BlasScale(tmd);
              S.Velocity().BlasShift(-1.,S.Gradient());
              this->Proj*=tmd;
              dnorm=__SqRoot(tmd*tmd+fnorm2-2*this->Proj);
              this->Proj-=fnorm2;
              this->Proj/=dnorm;
              isSteep=((this->Proj>0)||(dnorm<gTH));
            }
            if(isSteep) {
              if(fnorm<gTH) { fg=4; break; }
              beta=0.;
              dnorm=fnorm;
              S.Velocity().BlasCopy(S.Gradient());
              S.Velocity().BlasScale(-1.);
              this->Proj=-fnorm;
            }
            tmd=1./dnorm;
            S.Velocity().BlasScale(tmd);
            _OldG.BlasCopy(S.Gradient());
            tmd=S.Energy();
            lfg=ParentType::Evolute(S);
            ++Value<unsigned int>(this->_param[ConjgMinimizer_LineSearchCount]);
            nextMode=false;
            if(lfg==2) {
              if(isSteep) { fg=1; break; }
              else { --i; nextMode=true; }
            } else if(lfg==0) {
              fg=5; break;
            } else {
              tmd2=S.Energy();
              if(2*AbsVal(tmd-tmd2)<AbsVal(tmd+tmd2)*_RelDelta<T>()) {
                if(isSteep) { fg=2; break; }
                else { --i; nextMode=true; }
              }
            }
            isSteep=nextMode;
            oldfnorm2=fnorm2;
            fnorm=S.Gradient().BlasNorm();
            fnorm2=fnorm*fnorm;
          }
        }
        return fg;
      }

    protected:

      Array2DNumeric<T> _OldG;

    private:

      PropagatorConjugateGradientMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      virtual void IndependentModule() {}

  };

  template <typename T,typename GT,template<typename,typename> class LM>
  void Clear(PropagatorConjugateGradientMinimizer<T,GT,LM>& M) {
    Clear(M._OldG);
    typedef typename PropagatorConjugateGradientMinimizer<T,GT,LM>::ParentType
                     PType;
    Clear(static_cast<PType&>(M));
  }

}

#endif

