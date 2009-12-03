
#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "property-op.h"
#include "interaction-4listset.h"
#include "ref-vector.h"
#include <cmath>

namespace std {

  double MinimalStep4(const varVector<Property>& PropSet,
                      const varVector<varVector<double> >& Dirc) {
    uint n=PropSet.size(),dn;
    long ndeg=0;
    Property const *nowP;
    double MinStep=0, tmd, tmdc;
    for(uint i=0;i<n;++i) {
      nowP=&PropSet[i];
      dn=Dirc[i].size();
      for(uint j=0;j<dn;++j) {
        if(nowP->Mask[j]==0) continue;
        tmd=fabs(nowP->Coordinate[j]);
        tmdc=Dirc[i][j];
        tmd=(tmd<1.0?tmdc:tmdc/tmd);
        MinStep+=tmd*tmd;
      }
      ndeg+=dn;
    }
    return DRelDelta*sqrt(static_cast<double>(ndeg)/MinStep); 
  }

  template <typename DistEvalObj, typename GeomType>
  class MinimizerKern {

    public:

      refVector<Property> runSys;

      varVector<Property> MinSys;      
      
      double              MinE;
      
      ParamList           *runParamPtr;

      varVector<IDList<DistEvalObj,GeomType> >
                          *runIDLSPtr;
      
      DistEvalObj         *runDEvalPtr;
      
      GeomType            *runGeoPtr;
      
      double              MinPrj;
      
      double              MinMove;
      
      uint                MinGCount;
      
      double              MinScale;
      
      MinimizerKern()
        : runSys(), MinSys(), MinE(0.), runParamPtr(NULL), runDEvalPtr(NULL),
          runGeoPtr(NULL), MinPrj(0.), MinMove(0.), MinGCount(0),
          MinScale(0.1) {
      } 

      void Import(const varVector<Property>& vProp, const DistEvalObj& DEval,
                  const ParamList& PList,
                  const varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                  const GeomType& Geo, const double& E) {
        uint n=vProp.size();
        MinSys.allocate(n);
        for(uint i=0;i<n;++i) {
          copy_minimize_structure(MinSys[i],vProp[i]);
          copy_minimize_data(MinSys[i],vProp[i]);
        }
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
    
      void Update(const double& runStep, const varVector<Property>& Orig,
                  const varVector<varVector<double> >& Dirc,
                  varVector<Property>& rSys, double& E, double& Prj) {
        uint n=rSys.size();
        for(uint i=0;i<n;++i) {
          rSys[i].Coordinate=Orig[i].Coordinate;
          rSys[i].Coordinate.shift(runStep,Dirc[i]);
          rSys[i].Gradient=0.;
        }
        this->runSys.refer(rSys);
        this->runDEvalPtr->Update();
        E=0.;
        EG_ListSet(this->runSys,*(this->runParamPtr),*(this->runIDLSPtr),
                   *(this->runDEvalPtr),*(this->runGeoPtr),E);
        ++(this->MinGCount);
        Prj=0.;
        for(uint i=0;i<n;++i) Prj+=dot(rSys[i].Gradient,Dirc[i]);
      }

      varVector<Property> UppSys, LowSys, MidSys;

      double              UppE,   LowE,   MidE;

      double              UppP,   LowP,   MidP;

    public:

      void SetStep(const double& step) { Step=step; }

      void Import(const varVector<Property>& vProp, const DistEvalObj& DEval,
                  const ParamList& PList,
                  const varVector<IDList<DistEvalObj,GeomType> >& IDLS,
                  const GeomType& Geo, const double& E) {
        static_cast<ParentType*>(this)->Import(vProp,DEval,PList,IDLS,Geo,E);
        uint n=vProp.size();
        UppSys.allocate(n);
        LowSys.allocate(n);
        MidSys.allocate(n);
        for(uint i=0;i<n;++i) {
          copy_minimize_structure(UppSys[i],vProp[i]);
          copy_minimize_structure(LowSys[i],vProp[i]);
          copy_minimize_structure(MidSys[i],vProp[i]);
          copy_minimize_data(UppSys[i],vProp[i]);
          copy_minimize_data(LowSys[i],vProp[i]);
          copy_minimize_data(MidSys[i],vProp[i]);
        }
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

