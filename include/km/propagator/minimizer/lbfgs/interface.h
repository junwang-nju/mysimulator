
#ifndef _Propagator_Minimizer_LBFGS_Interface_H_
#define _Propagator_Minimizer_LBFGS_Interface_H_

#include "propagator/minimizer/interface.h"
#include "propagator/minimizer/lbfgs/parameter-name.h"

namespace mysimulator {

  template <typename T,typename GT,template<typename,typename> class LM>
  class PropagatorLBFGSMinimizer;
  template <typename T,typename GT,template<typename,typename> class LM>
  void Clear(PropagatorLBFGSMinimizer<T,GT,LM>&);

  template <typename T,typename GT,
            template<typename,typename> class LineMinimizer=
                                              PropagatorTrackingLineMinimizer>
  class PropagatorLBFGSMinimizer
      : public PropagatorMinimizer<T,GT,LineMinimizer> {

    public:

      typedef PropagatorLBFGSMinimizer<T,GT,LineMinimizer>    Type;
      typedef PropagatorMinimizer<T,GT,LineMinimizer>   ParentType;
      friend void Clear<T,GT,LineMinimizer>(Type&);

      PropagatorLBFGSMinimizer() : ParentType(), dX(), dG(), alpha(),
                                   rho(), lastX(), lastG() {}
      ~PropagatorLBFGSMinimizer() { Clear(*this); }

      virtual bool IsValid() const {
        return ParentType::IsValid()&&dX.IsValid()&&dG.IsValid()&&
               alpha.IsValid()&&rho.IsValid()&&lastX.IsValid()&&
               lastG.IsValid();
      }
      virtual void IntroduceSystem(System<T,GT>& S) {
        ParentType::IntroduceSystem(S);
        for(unsigned int i=0;i<dX.Size();++i)
          dX[i].Imprint(S.Location());
        for(unsigned int i=0;i<dG.Size();++i)
          dG[i].Imprint(S.Location());
        lastX.Imprint(S.Location());
        lastG.Imprint(S.Location());
      }
      virtual void DetachSystem() {
        ParentType::DetachSystem();
        Clear(lastG);
        Clear(lastX);
        for(unsigned int i=0;i<dG.Size();++i) Clear(dG[i]);
        for(unsigned int i=0;i<dX.Size();++i) Clear(dX[i]);
      }

      virtual void Update() {
        ParentType::Update();
        if(Value<unsigned int>(this->_param[LBFGSMinimizer_MaxStep])==0)
          Value<unsigned int>(this->_param[LBFGSMinimizer_MaxStep])=1000;
      }
      virtual void Allocate(const Array<StepPropagatorName>& PN,...) {
        ParentType::Allocate(PN);
        this->_tag=LBFGSMinimizer;
        this->_param.Allocate(LBFGSMinimizer_NumberParameter);
        ParentType::BuildLine();
        va_list vl;
        va_start(vl,PN);
        Value<unsigned int>(this->_param[LBFGSMinimizer_MaxCorrelation])=
          va_arg(vl,unsigned int);
        va_end(vl);
        const unsigned int n=
          Value<unsigned int>(this->_param[LBFGSMinimizer_MaxCorrelation]);
        alpha.Allocate(n);
        rho.Allocate(n);
        dX.Allocate(n);
        dG.Allocate(n);
      }

      virtual unsigned int Evolute(System<T,GT>& S) {
        assert(IsValid());
        Value<unsigned int>(this->_param[BaseMin_GCalcCount])=0;
        Value<unsigned int>(this->_param[LBFGSMinimizer_LineSearchCount])=0;
        unsigned int fg, lfg;
        fg=0;
        T fnorm=S.Gradient().BlasNorm();
        const T gTH=Value<T>(this->_param[LineMin_GradThreshold]);
        if(fnorm<gTH) fg=3;
        else {
          unsigned int ncr, point, cp;
          T diag,dgdg,dgdx,beta,dnorm,tmd,tmd2;
          bool isSteep, nextMode;
          ncr=0;
          point=0;
          fg=0;
          const unsigned int n=
            Value<unsigned int>(this->_param[LBFGSMinimizer_MaxStep]);
          const unsigned int maxCr=
            Value<unsigned int>(this->_param[LBFGSMinimizer_MaxCorrelation]);
          for(unsigned int i=0;i<n;++i) {
            if(!isSteep) {
              this->Proj=BlasDot(S.Velocity(),S.Gradient());
              dnorm=S.Velocity().BlasNorm();
              this->Proj/=dnorm;
              isSteep=((this->Proj>0)||(dnorm<gTH));
            }
            if(isSteep) {
              if(fnorm<gTH) { fg=4; break; }
              else {
                ncr=0;
                diag=1.;
                S.Velocity().BlasCopy(S.Gradient());
                S.Velocity().BlasScale(-diag);
                dnorm=fnorm*diag;
                this->Proj=-dnorm;
              }
            }
            S.Velocity().BlasScale(1./dnorm);
            dX[point].BlasCopy(S.Velocity());
            lastX.BlasCopy(S.Location());
            lastG.BlasCopy(S.Gradient());
            tmd=S.Energy();
            lfg=ParentType::Evolute(S);
            ++Value<unsigned int>(this->_param[LBFGSMinimizer_LineSearchCount]);
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
            fnorm=S.Gradient().BlasNorm();
            if(!isSteep) {
              if(ncr<maxCr) ++ncr;
              dG[point].BlasCopy(S.Gradient());
              dG[point].BlasShift(-1.,lastG);
              dX[point].BlasScale(this->Move);
              dgdg=dG[point].BlasNormSQ();
              dgdx=BlasDot(dG[point],dX[point]);
              diag=dgdx/dgdg;
              rho[point]=1./dgdx;
              ++point;
              if(point>=maxCr)  point=0;
              S.Velocity().BlasCopy(S.Gradient());
              S.Velocity().BlasScale(-1.);
              cp=point;
              for(unsigned int k=0;k<ncr;++k) {
                cp=(cp==0?ncr-1:cp-1);
                alpha[cp]=rho[cp]*BlasDot(dX[cp],S.Velocity());
                S.Velocity().BlasShift(-alpha[cp],dG[cp]);
              }
              S.Velocity().BlasScale(diag);
              for(unsigned int k=0;k<ncr;++k) {
                beta=alpha[cp]-rho[cp]*BlasDot(S.Velocity(),dG[cp]);
                S.Velocity().BlasShift(beta,dX[cp]);
                cp=(cp==ncr-1?0:cp+1);
              }
            }
          }
        }
        return fg;
      }

    protected:

      Array<Array2DNumeric<T> >   dX;
      Array<Array2DNumeric<T> >   dG;
      ArrayNumeric<T>             alpha;
      ArrayNumeric<T>             rho;
      Array2DNumeric<T>           lastX;
      Array2DNumeric<T>           lastG;

    private:

      PropagatorLBFGSMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      virtual void IndependentModule() {}

  };

  template <typename T,typename GT,template<typename,typename> class LM>
  void Clear(PropagatorLBFGSMinimizer<T,GT,LM>& M) {
    Clear(M.lastG);
    Clear(M.lastX);
    Clear(M.rho);
    Clear(M.alpha);
    Clear(M.dG);
    Clear(M.dX);
    typedef typename PropagatorLBFGSMinimizer<T,GT,LM>::ParentType  PType;
    Clear(static_cast<PType&>(M));
  }

}

#endif

