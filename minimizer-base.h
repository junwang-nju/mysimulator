
#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "memory.h"
#include "var-vector.h"

namespace std {

  template <typename SpaceType, typename ParameterType>
  class MinimizerKernBase {

    public:
      typedef void (*YFuncType)(const SpaceType&,ParameterType&,
                                double&);
      typedef void (*GFuncType)(const SpaceType&,ParameterType&,
                                SpaceType*);
      typedef void (*BFuncType)(const SpaceType&,ParameterType&,
                                double&,SpaceType&);
      YFuncType                 YFunc;
      GFuncType                 GFunc;
      BFuncType                 BFunc;
      SpaceType                 MinCoor;
      double                    MinY;
      SpaceType                 MinGrad;
      ParameterType             *pRunParam;
      double                    MinPrj;
      double                    MinMove;
      uint                      MinGCount;
      double                    MinScale;

      MinimizerKernBase() : YFunc(NULL), GFunc(NULL), BFunc(NULL),
                            MinCoor(), MinY(0.), MinGrad(),
                            pRunParam(NULL), MinPrj(0.), MinMove(0.),
                            MinGCount(0), MinScale(0.1) {}
      void clear() {
        YFunc=NULL;
        GFunc=NULL;
        BFunc=NULL;
        pRunParam=NULL;
      }

      void ImportFunc(const YFuncType& YF,const GFuncType& GF,
                      const BFuncType& BF) {
        YFunc=const_cast<YFuncType&>(YF);
        GFunc=const_cast<GFuncType&>(GF);
        BFunc=const_cast<BFuncType&>(BF);
      }

      virtual void ImportState(const SpaceType&,const ParameterType&)=0;

  };

  enum ConditionType {
    Armijo=0,
    Wolfe,
    StrongWolfe
  };

  template <uint CondType>
  bool Condition(const double&,const double&,const double&,
                 const double&,const double&,const double&) {
    myError("Unknown Condition Type!");
    return false;
  }

  template <>
  bool Condition<Armijo>(const double& ry, const double& rp,
                         const double& my,
                         const double& dp, const double& cp,
                         const double& step) {
    return ry<=my+step*dp;
  }

  template <>
  bool Condition<Wolfe>(const double& ry, const double& rp,
                        const double& my,
                        const double& dp, const double& cp,
                        const double& step) {
    assert(cp<0);
    return Condition<Armijo>(ry,rp,my,dp,cp,step)&&(rp>=cp);
  }

  template <>
  bool Condition<StrongWolfe>(const double& ry, const double& rp,
                              const double& my,
                              const double& dp, const double& cp,
                              const double& step) {
    return Condition<Wolfe>(ry,rp,my,dp,cp,step)&&(rp<=-cp);
  }

  template <typename SpaceType, typename ParameterType>
  class LineMinimizerBase
    : public MinimizerKernBase<SpaceType,ParameterType> {

    public:
      typedef LineMinimizerBase<SpaceType,ParameterType> Type;
      typedef MinimizerKernBase<SpaceType,ParameterType> ParentType;

    protected:
      SpaceType RunCoor;
      SpaceType RunGrad;
      double    RunY;
      double    RunPrj;
      double    DecreaseFac;
      double    CurvatureFac;

    public:
      LineMinimizerBase() : ParentType(),
                            RunCoor(), RunGrad(), RunY(0.), RunPrj(0.),
                            DecreaseFac(1e-4), CurvatureFac(0.4) {}
      void SetDecreaseFactor(const double& dfac) { DecreaseFac=dfac; }
      void SetCurvatureFactor(const double& cfac) { CurvatureFac=cfac; }

    protected:

      void Propagate(const SpaceType& Origin, const SpaceType& Dirc,
                     const double& step,
                     SpaceType& Dest, double& DestY, SpaceType& DestG,
                     double& DestPrj) {
        Dest=Origin;
        Dest.shift(step,Dirc);
        DestY=0.;
        DestG=0.;
        this->BFunc(Dest,*(this->pRunParam),DestY,DestG);
        ++(this->MinGCount);
        DestPrj=dot(DestG,Dirc);
      }

      double MinStep(const SpaceType& Origin, const SpaceType& Dirc) = 0;

  };

  template <typename SpaceType, typename ParameterType,
            uint CondType=StrongWolfe>
  class BacktrackingLineMinimizer
    : public LineMinimizerBase<SpaceType,ParameterType>{
    public:
      typedef BacktrackingLineMinimizer<SpaceType,ParameterType,CondType> Type;
      typedef LineMinimizerBase<SpaceType,ParameterType>            ParentType;

    private:
      double BacktrackFac;

    public:
      BacktrackingLineMinimizer() : ParentType(), BacktrackFac(Gold) {}
      void SetBacktrackingFactor(const double& bfac) { BacktrackFac=bfac; }
      int Go(SpaceType& Dirc) {
        this->MinPrj=dot(Dirc,this->MinGrad);
        if(this->MinPrj>DRelDelta)  { Dirc*=-1.; this->MinPrj=-this->MinPrj; }
        else if(this->MinPrj>=-DRelDelta) return 2;
        const double minstep=MinStep(this->MinCoor,Dirc);
        double step=this->MinScale;
        double c1pj=this->DecreaseFac*this->MinPrj;
        double c2pj=this->CurvatureFac*this->MinPrj;
        do {
          Propagate(this->MinCoor,Dirc,step,
                    this->RunCoor,this->RunY,this->RunGrad,this->RunPrj);
          if(Condition<CondType>(this->RunY,this->RunPrj,this->MinY,
                                 c1pj,c2pj,step)) {
            swap(this->MinCoor,this->RunCoor);
            this->MinY=this->RunY;
            swap(this->MinGrad,this->RunGrad);
            this->MinPrj=this->RunPrj;
            this->MinMove=step;
            return 1;
          }
          step*=BacktrackFac;
        } while(step>minstep);
        return 2;
      }
  };

}

#endif

