
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

}

#endif

