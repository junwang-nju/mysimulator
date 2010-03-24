
#ifndef _Minimizer_Line_Base_H_
#define _Minimizer_Line_Base_H_

#include "minimizer-base.h"

namespace std {

  enum ConditionType {
    Armijo=0,
    Wolfe,
    StrongWolfe
  };

  template <int CondType>
  bool Condition(const double&, const double&, const double&,
                 const double&, const double&, const double&) {
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

  template <typename SpaceVecType, typename ParameterType>
  class LineMinmizerBase
    : public MinimizerKernelBase<SpaceVecType,ParameterType> {

    public:

      typedef LineMinmizerBase<SpaceVecType,ParameterType>  Type;

      typedef MinimizerKernelBase<SpaceVecType,ParameterType>   ParentType;

      unsigned int MinLineCount;

    protected:

      SpaceVecType   RunCoor;
      SpaceVecType   RunGrad;
      double         RunY;
      double         RunPrj;
      double         DecreaseFac;
      double         CurvatureFac;
      double         GradThreshold;

    public:

      LineMinmizerBase() : ParentType(), MinLineCount(0), RunCoor(), RunGrad(),
                           RunY(0.), RunPrj(0.), DecreaseFac(1e-4),
                           CurvatureFac(0.4), GradThreshold(DRelDelta) {
      }

      LineMinmizerBase(const Type& LMB) {
        myError("Cannot create from Line Minimizer Base");
      }

      ~LineMinmizerBase() { clear(); }

      void clear() {
        MinLineCount=0;
        RunCoor.clear();
        RunGrad.clear();
        RunY=0.;
        RunPrj=0.;
        DecreaseFac=0.;
        CurvatureFac=0.;
        GradThreshold=0.;
      }

      Type& operator=(const Type& LMB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(LMB));
        MinLineCount=LMB.MinLineCount;
        RunCoor=LMB.RunCoor;
        RunGrad=LMB.RunGrad;
        RunY=LMB.RunY;
        RunPrj=LMB.RunPrj;
        DecreaseFac=LMB.DecreaseFac;
        CurvatureFac=LMB.CurvatureFac;
        GradThreshold=LMB.GradThreshold;
        return *this;
      }

      void SetDecreaseFactor(const double dfac) { DecreaseFac=dfac; }

      void SetCurvatureFactor(const double cfac) { CurvatureFac=cfac; }

      void SetGradientThreshold(const double gth) { GradThreshold=gth; }

    protected:

      void Propagate(const SpaceVecType& Origin, const SpaceVecType& Dirc,
                     const double step, SpaceVecType& Dest, double& DestY,
                     SpaceVecType& DestG, double& DestPrj) {
        Dest=Origin;
        Dest.shift(step,Dirc);
        static_cast<ParentType*>(this)->MinParam.update();
        DestY=0.;
        DestG=0.;
        static_cast<ParentType*>(this)->MinBFunc(Dest,DestY,DestG,
            static_cast<ParentType*>(this)->MinParam);
        ++(static_cast<ParentType*>(this)->MinGCount);
        DestPrj=dot(DestG,Dirc);
      }

  };

}

#endif

