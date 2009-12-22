
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
      GradientType              MinGrad;
      ParameterType             *pRunParam;
      double                    MinPrj;
      double                    MinMove;
      uint                      MinGCount;
      double                    MinScale;

      MinimizerKernBase() : YFunc(NULL), GFunc(NULL), BFunc(NULL),
                            pMinCoor(NULL), MinY(0.), pMinGrad(NULL),
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

  template <typename SpaceType, typename ParameterType>
  class LineMinimizerBase
    : public MinimizerKernBase<SpaceType,ParameterType> {

    public:
      typedef LineMinimizerBase<SpaceType,ParameterType> Type;
      typedef MinimizerKern<SpaceType,ParameterType>     ParentType;

      SpaceType pUppCoor,pLowCoor,pMidCoor;
      SpaceType pUppGrad,pLowGrad,pMidGrad;
      double    UppY,    LowY,    MidY;

      LineMinimizerBase() : ParentType(),
                            UppCoor(), LowCoor(), MidCoor(),
                            UppGrad(), LowGrad(), MidGrad(),
                            UppY(0.), LowY(0.), MidY(0.) {}
    protected:

      template <typename vType>
      void Propagate(const SpaceType& Origin, const vType& Dirc,
                     const double& step,
                     SpaceType& Dest, double& DestY, SpaceType& DestG,
                     double& Dest Prj) {
        Dest=Origin;
        Dest.shift(step,Dirc);
        DestY=0.;
        DestG=0.;
        this->BFunc(Dest,*(this->pRunParam),DestY,DestG);
        ++(this->MinGCount);
        DestPrj=dot(DestG,Dirc);
      }

  };

  template <>
  class LineMinimizer<varVector<double>,varVector<double> >
    : public MinimizerKern<varVector<double>,varVector<double> > {
    public:
      typedef varVector<double> DVecType;
      typedef LineMinimizer<DVecType,DVecType>    Type;
      typedef MinimizerKern<DVecType,DVecType>    ParentType;
  };

}

#endif

