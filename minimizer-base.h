
#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "memory.h"
#include "var-vector.h"

namespace std {

  template <typename CoordinateType, typename ParameterType>
  class MinimizerKernBase {

    public:
      typedef void (*YFuncType)(const CoordinateType*,ParameterType*,
                                double&);
      typedef void (*GFuncType)(const CoordinateType*,ParameterType*,
                                CoordinateType*);
      typedef void (*BFuncType)(const CoordinateType*,ParameterType*,
                                double&,CoordinateType*);
      YFuncType                 YFunc;
      GFuncType                 GFunc;
      BFuncType                 BFunc;
      CoordinateType            MinCoor;
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

  };

  template <typename CoordinateType, typename ParameterType>
  class MinimizerKern : public MinimizerKernBase<CoordinateType,ParameterType>{
    public:
      typedef MinimizerKern<CoordinateType,ParameterType>     Type;
      typedef MinimizerKernBase<CoordinateType,ParameterType> ParentType;
      MinimizerKern() : ParentType() {}
      virtual void ImportState(const CoordinateType&,const ParameterType&)=0;
  };

  template <>
  class MinimizerKern<varVector<double>,varVector<double> >
    : public MinimizerKernBase<varVector<double>,varVector<double> > {
    public:
      typedef varVector<double> DVecType;
      typedef MinimizerKern<DVecType,DVecType>      Type;
      typedef MinimizerKernBase<DVecType,DVecType>  ParentType;
      MinimizerKern() : ParentType() {}
      void ImportState(const DVecType& Coor, const DVecType& Param) {
        assert(this->BFunc!=NULL);
        this->pMinCoor=new DVecType;
        this->pMinCoor->allocate(Coor);
        *(this->pMinCoor)=Coor;
        this->pMinGrad=new DVecType;
        this->pMinGrad.allocate(Coor);
        MinY=0.;
        *(this->pMinGrad)=0.;
        BFunc(this->pMinCoor,this->pRunParam,MinY,this->pMinGrad);
      }
  };

  template <typename CoordinateType, typename ParameterType>
  class LineMinimizerBase
    : public MinimizerKern<CoordinateType,ParameterType> {

    public:
      typedef LineMinimizerBase<CoordinateType,ParameterType> Type;
      typedef MinimizerKern<CoordinateType,ParameterType>     ParentType;

      CoordinateType  *pUppCoor,*pLowCoor,*pMidCoor;
      CoordinateType  *pUppGrad,*pLowGrad,*pMidGrad;
      double          UppY,   LowY,   MidY;

      LineMinimizerBase() : ParentType(),
                            pUppCoor(NULL), pLowCoor(NULL), pMidCoor(NULL),
                            pUppGrad(NULL), pLowGrad(NULL), pMidGrad(NULL),
                            UppY(0.), LowY(0.), MidY(0.) {}

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

