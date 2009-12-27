
#ifndef _Minimizer_Line_Base_H_
#define _Minimizer_Line_Base_H_

#include "minimizer-base.h"

namespace std {

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
      typedef SpaceType                                  RunSpaceType;

      uint      MinLineCount;

    protected:
      SpaceType RunCoor;
      SpaceType RunGrad;
      double    RunY;
      double    RunPrj;
      double    DecreaseFac;
      double    CurvatureFac;
      double    GradThreshold;

    public:
      LineMinimizerBase() : ParentType(), MinLineCount(0),
                            RunCoor(), RunGrad(), RunY(0.), RunPrj(0.),
                            DecreaseFac(1e-4), CurvatureFac(0.4),
                            GradThreshold(DRelDelta) { }
      void SetDecreaseFactor(const double& dfac) { DecreaseFac=dfac; }
      void SetCurvatureFactor(const double& cfac) { CurvatureFac=cfac; }
      void SetGradientThreshold(const double& gth) { GradThreshold=gth; }

    protected:

      void Propagate(const SpaceType& Origin, const SpaceType& Dirc,
                     const double& step,
                     SpaceType& Dest, double& DestY, SpaceType& DestG,
                     double& DestPrj) {
        Dest=Origin;
        Dest.shift(step,Dirc);
        this->pRunParam->Update();
        DestY=0.;
        DestG=0.;
        this->BFunc(Dest,*(this->pRunParam),DestY,DestG);
        ++(this->MinGCount);
        DestPrj=dot(DestG,Dirc);
      }

      virtual
      double MinStep(const SpaceType& Origin, const SpaceType& Dirc) = 0;

  };

}

#endif

