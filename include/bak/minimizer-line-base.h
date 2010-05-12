
#ifndef _Minimizer_Line_Base_H_
#define _Minimizer_Line_Base_H_

#include "minimizer-base.h"

namespace std {

  template <typename SpaceVecType, typename ParameterType>
  class LineMinmizerBase
    : public MinimizerKernelBase<SpaceVecType,ParameterType> {

    public:

      typedef LineMinmizerBase<SpaceVecType,ParameterType>  Type;

      typedef MinimizerKernelBase<SpaceVecType,ParameterType>   ParentType;

      typedef SpaceVecType  RunSpaceVecType;

      unsigned int MinLineCount;

    protected:

      SpaceVecType   RunCoor;
      SpaceVecType   RunGrad;
      double         RunE;
      double         RunPrj;
      double         DecreaseFac;
      double         CurvatureFac;
      double         GradThreshold;

    public:

      LineMinmizerBase() : ParentType(), MinLineCount(0), RunCoor(), RunGrad(),
                           RunE(0.), RunPrj(0.), DecreaseFac(1e-4),
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
        RunE=0.;
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
        RunE=LMB.RunE;
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

