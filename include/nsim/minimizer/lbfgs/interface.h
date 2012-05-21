
#ifndef _Minimizer_LBFGS_Interface_H_
#define _Minimizer_LBFGS_Interface_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  struct Minimizer<LBFGS,LMN,T,IDT,PT,GT,BT,CT,LMC>
      : public LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC> {

    public:

      typedef Minimizer<LBFGS,LMN,T,IDT,PT,GT,BT,CT,LMC>    Type;
      typedef LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC>      ParentType;

      static const unsigned int DefaultMaxSteps;

      unsigned int MaxCorrelations;
      Array1D<Array2D<T> >    dX,dG;
      Array1D<T>              alpha,rho;
      Array2D<T>              lastX,lastG;

      Minimizer() : ParentType(), MaxCorrelations(0), dX(),dG(),alpha(),
                    rho(),lastX(),lastG() {}
      ~Minimizer() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               dX.IsValid()&&dG.IsValid()&&alpha.IsValid()&&rho.IsValid()&&
               lastX.IsValid()&&lastG.IsValid()&&(MaxCorrelations>0);
      }

      void Load(System<T,IDT,PT,GT,BT,CT>& S) {
        static_cast<ParentType*>(this)->Load(S);
        if(MaxCorrelations==0)  SetMaxCorrelations();
        dX.Allocate(MaxCorrelations);
        dG.Allocate(MaxCorrelations);
        for(unsigned int i=0;i<MaxCorrelations;++i) {
          Imprint(dX[i],S.Content.X);
          Imprint(dG[i],S.Content.X);
        }
        alpha.Allocate(MaxCorrelations);
        rho.Allocate(MaxCorrelations);
        Imprint(lastX,S.Content.X);
        Imprint(lastG,S.Content.X);
      }

      void SetMaxCorrelations() { MaxCorrelations=6; }
      void SetMaxCorrelations(unsigned int C) { MaxCorrelations=C; }

      int Go(unsigned int MaxSteps=DefaultMaxSteps) {
        assert(IsValid());
        this->GCalcCount=0;
        this->LineSearchCount=0;
        _Load2Mem(*this);
        unsigned int ncr=0, point=0, cp;
        T diag,dgdg,dgdx,beta,fnorm,dnorm,tmd,tmd2;
        fnorm=BlasNorm(this->MemSys->Content.EGData.Gradient);
        if(fnorm<this->GradThreshold)   return 3;
        bool isSteep=true, nextMode;
        unsigned int fg=0, lfg;
        for(unsigned int nr=0;nr<MaxSteps;++nr) {
          if(!isSteep) {
            this->Proj=BlasDot(this->LineDirc,
                               this->MemSys->Content.EGData.Gradient);
            dnorm=BlasNorm(this->LineDirc);
            this->Proj/=dnorm;
            isSteep=((this->Proj>0)||(dnorm<this->GradThreshold));
          }
          if(isSteep) {
            if(fnorm<this->GradThreshold) { fg=4; break; }
            else {
              ncr=0;
              diag=1.;
              BlasCopy(this->LineDirc,this->MemSys->Content.EGData.Gradient);
              BlasScale(this->LineDirc,-diag);
              dnorm=fnorm*diag;
              this->Proj=-dnorm;
            }
          }
          BlasScale(this->LineDirc,1./dnorm);
          BlasCopy(dX[point],this->LineDirc);
          BlasCopy(lastX,this->MemSys->Content.X);
          BlasCopy(lastG,this->MemSys->Content.EGData.Gradient);
          tmd=this->MemSys->Content.EGData.Energy[0];
          lfg=static_cast<ParentType*>(this)->Go();
          this->LineSearchCount++;
          nextMode=false;
          if(lfg==2) {
            if(isSteep) { fg=1; break; }
            else { --nr; nextMode=true; }
          } else if(lfg==0) { fg=5; break; }
          else {
            tmd2=this->MemSys->Content.EGData.Energy[0];
            if(2*absval(tmd-tmd2)<absval(tmd+tmd2)*RelDelta<T>()) {
              if(isSteep) { fg=2; break; }
              else { --nr; nextMode=true; }
            }
          }
          isSteep=nextMode;
          fnorm=BlasNorm(this->MemSys->Content.EGData.Gradient);
          if(!isSteep) {
            if(ncr<MaxCorrelations)   ++ncr;
            BlasCopy(dG[point],this->MemSys->Content.EGData.Gradient);
            BlasShift(dG[point],-1.,lastG);
            BlasScale(dX[point],this->Move);
            dgdg=BlasNormSQ(dG[point]);
            dgdx=BlasDot(dG[point],dX[point]);
            diag=dgdx/dgdg;
            rho[point]=1./dgdx;
            ++point;
            if(point>=MaxCorrelations)  point=0;
            BlasCopy(this->LineDirc,this->MemSys->Content.EGData.Gradient);
            BlasScale(this->LineDirc,-1.);
            cp=point;
            for(unsigned int k=0;k<ncr;++k) {
              cp=(cp==0?ncr-1:cp-1);
              alpha[cp]=rho[cp]*BlasDot(dX[cp],this->LineDirc);
              BlasShift(this->LineDirc,-alpha[cp],dG[cp]);
            }
            BlasScale(this->LineDirc,diag);
            for(unsigned int k=0;k<ncr;++k) {
              beta=alpha[cp]-rho[cp]*BlasDot(this->LineDirc,dG[cp]);
              BlasShift(this->LineDirc,beta,dX[cp]);
              cp=(cp==ncr-1?0:cp+1);
            }
          }
        }
        _Write2Sys(*this);
        return fg;
      }

  };

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  const unsigned int
  Minimizer<LBFGS,LMN,T,IDT,PT,GT,BT,CT,LMC>::DefaultMaxSteps=1000;

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  void Clear(Minimizer<LBFGS,LMN,T,IDT,PT,GT,BT,CT,LMC>& M) {
    M.MaxCorrelations=0;
    Clear(M.dX);
    Clear(M.dG);
    Clear(M.alpha);
    Clear(M.rho);
    Clear(M.lastX);
    Clear(M.lastG);
    typedef typename Minimizer<LBFGS,LMN,T,IDT,PT,GT,BT,CT,LMC>::ParentType
            Type;
    Clear(static_cast<Type&>(M));
  }

}

#endif

