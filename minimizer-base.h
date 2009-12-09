
#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "property-list.h"
#include "interaction-4listset.h"
#include "ref-vector.h"
#include <cmath>

namespace std {

  double MinimalStep4(const VectorBase<double>& X,
                      const VectorBase<double>& Dirc,
                      const VectorBase<uint>& Fg) {
    uint n=X.size();
    assert(n==Dirc.size());
    assert(n==Fg.size());
    double MinStep=0.,tmd,ndeg=0.;
    for(uint i=0;i<n;++i) {
      if(Fg[i]==0)  continue;
      tmd=fabs(X[i]);
      tmd=(tmd<1.0?Dirc[i]:Dirc[i]/tmd);
      MinStep+=tmd*tmd;
      ndeg+=1.;
    }
    return DRelDelta*sqrt(ndeg/MinStep); 
  }

  template <typename DistEvalObj, typename GeomType>
  class MinimizerKern {

    protected:
      void allocateSystem4Minimize(PropertyList& PList,
                                   const VectorBase<Property>& iPList) {
        uint n=iPList.size();
        varVector<uint> MType(n),MFlag(n);
        for(uint i=0;i<n;++i) {
          MType[i]=iPList[i].Info[MonomerTypeID];
          MFlag[i]=GradientEnable;
        }
        PList.gAllocate(MType,MFlag,iPList[0].Info[MonomerDimension]);
      }

      void copySystem4Minimization(PropertyList& PList,
                                   const PropertyList& iPList) {
        // here assume that PList and iPList have the same structure
        PList.gInfo=iPList.gInfo;
        PList.gCoordinate=iPList.gCoordinate;
        PList.gMask=iPList.gMask;
        PList.gDMask=iPList.gDMask;
        PList.gGradient=iPList.gGradient;
        if(PList.gInCoordinate.isAvailable())
          PList.gInCoordinate=iPList.gInCoordinate;
        if(PList.gInGradient.isAvailable())
          PList.gInGradient=iPList.gInGradient;
      }

    public:

      PropertyList        MinSys;      
      
      double              MinE;
      
      ParamList*          runParamPtr;

      varVector<IDList<DistEvalObj,GeomType> >*
                          runIDLSPtr;
      
      DistEvalObj*        runDEvalPtr;
      
      GeomType*           runGeoPtr;
      
      double              MinPrj;
      
      double              MinMove;
      
      uint                MinGCount;
      
      double              MinScale;
      
      MinimizerKern()
        : MinSys(), MinE(0.), runParamPtr(NULL), runDEvalPtr(NULL),
          runGeoPtr(NULL), MinPrj(0.), MinMove(0.), MinGCount(0),
          MinScale(0.1) {
      } 

      void Import(const PropertyList& iPList, const DistEvalObj& DEval,
                  const ParamList& PList,
                  const varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                  const GeomType& Geo, const double& E) {
        allocateSystem4Minimize(MinSys,iPList);
        copySystem4Minimization(MinSys,iPList);
        runDEvalPtr=const_cast<DistEvalObj*>(&DEval);
        runParamPtr=const_cast<ParamList*>(&PList);
        runIDLSPtr
          =const_cast<varVector<IDList<DistEvalObj,GeomType> >*>(&IDLS);
        runGeoPtr=const_cast<GeomType*>(&Geo);
        MinE=E;
      }

  };

  template <typename DistEvalObj, typename GeomType>
  class CoarseMinimizerKern : public MinimizerKern<DistEvalObj,GeomType> {

    public:
    
      typedef CoarseMinimizerKern<DistEvalObj,GeomType>   Type;
      
      typedef MinimizerKern<DistEvalObj,GeomType>         ParentType;

      double Step;
      
      static const uint DefaultMaxIter;
      
    private:
    
      void Update(const double& runStep, const VectorBase<double>& Orig,
                  const VectorBase<double>& Dirc,
                  PropertyList& rSys, double& E, double& Prj) {
        rSys.gCoordinate=Orig;
        rSys.gCoordinate.shift(runStep,Dirc);
        rSys.gGradient=0.;
        this->runDEvalPtr->Update();
        E=0.;
        EG_ListSet(rSys,*(this->runParamPtr),*(this->runIDLSPtr),
                   *(this->runDEvalPtr),*(this->runGeoPtr),E);
        ++(this->MinGCount);
        Prj=dot(rSys.gGradient,Dirc);
      }

      PropertyList  UppSys, LowSys, MidSys;

      double        UppE,   LowE,   MidE;

      double        UppP,   LowP,   MidP;

    public:

      void SetStep(const double& step) { Step=step; }

      void Import(const PropertyList& iPList, const DistEvalObj& DEval,
                  const ParamList& PList,
                  const varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                  const GeomType& Geo, const double& E) {
        static_cast<ParentType*>(this)->Import(iPList,DEval,PList,IDLS,Geo,E);
        this->allocateSystem4Minimize(UppSys,iPList);
        this->allocateSystem4Minimize(LowSys,iPList);
        this->allocateSystem4Minimize(MidSys,iPList);
        this->copySystem4Minimization(UppSys,iPList);
        this->copySystem4Minimization(LowSys,iPList);
        this->copySystem4Minimization(MidSys,iPList);
      }

      int MinimizeAlongLine(const varVector<varVector<double> >& Dirc) {
        double a=0., b, c=Step;
        Update(Step,this->MinSys,Dirc,UppSys,UppE,UppP);
        double tmd;
        tmd=DSqrtRelDelta*fabs(this->MinE);
        if( (UppE<this->MinE) || ((UppP<0)&&(UppE<this->MinE+tmd)) ) {
          this->MinSys.swap(UppSys);
          this->MinE=UppE;
          this->MinMove=Step;
          Step*=(UppP<0?IvGold:Gold);
          return 1;
        } else  Step*=Gold;
        uint nEval=0;
        uint n=this->MinSys.size();
        for(uint i=0;i<n;++i) copy_minimize_data(LowSys[i],this->MinSys[i]);
        LowE=this->MinE;
        LowP=this->MinPrj;
        do {
          if( (LowP<0)&&(UppP>0) )  b=a+LowP*(a-c)/(UppP-LowP);
          else                      b=0.5*(a+c);
          if( (b<=a)||(b>=c) )      b=0.5*(a+c);
          Update(b,this->MinSys,Dirc,MidSys,MidE,MidP);
          if(MidP>0) {
            c=b;
            UppSys.swap(MidSys);
            UppE=MidE;
            UppP=MidP;
          } else {
            a=b;
            LowSys.swap(MidSys);
            LowE=MidE;
            LowP=MidP;
          }
          ++nEval;
        } while( ((MidE>UppE)||(MidE>LowE))&&(nEval<DefaultMaxIter) );
        if( (this->MinE-MidE<DRelDelta)||(nEval>=DefaultMaxIter) ) return 2;
        if(UppE<LowE) {
          this->MinSys.swap(UppSys);
          this->MinE=UppE;
          this->MinMove=c;
        } else {
          this->MinSys.swap(LowSys);
          this->MinE=LowE;
          this->MinMove=a;
        }
        return 1;
      }

  };

  template <typename DistEvalObj, typename GeomType>
  const uint CoarseMinimizerKern<DistEvalObj,GeomType>::DefaultMaxIter=20;

}

#endif

