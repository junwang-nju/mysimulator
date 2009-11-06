
#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "var-vector.h"
#include "property.h"
#include "property-op.h"
#include "param-list.h"
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
        if((nowP->Mask[j]<1e-16)&&(nowP->Mask[j]>-1e-16)) continue;
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

      varVector<Property> runSys;

      varVector<Property> MinSys;      
      
      double              MinY;
      
      ParamList           *runParamPtr;
      
      DistEvalObj         *runDEvalPtr;
      
      GeomType            *runGeoPtr;
      
      double              MinPrj;
      
      double              MinMove;
      
      uint                MinGCount;
      
      double              MinScale;
      
      MinimizerKern()
        : runSys(), MinSys(), MinY(0.), runParamPtr(NULL), runDEvalPtr(NULL),
          runGeoPtr(NULL), MinPrj(0.), MinMove(0.), MinGCount(0),
          MinScale(0.1) {
      } 

      void Import(const varVector<Property>& vProp, const DistEvalObj& DEval,
                  const ParamList& PList, const GeomType& Geo,
                  const double& E) {
        uint n=vProp.size();
        for(uint i=0;i<n;++i) {
          copy_structure(runSys[i],vProp[i]);
          copy_structure(MinSys[i],vProp[i]);
          runSys[i].Mask=vProp[i].Mask;
          MinSys[i].Coordinate=vProp[i].Coordinate;
          MinSys[i].Gradient=
        }
        runDEvalPtr=const_cast<DistEvalObj*>(&DEval);
        runParamPtr=const_cast<ParamList*>(&PList);
        runGeoPtr=const_cast<GeomType*>(&Geo);
        MinY=E;
      }

  };

  template <typename DistEvalObj, typename GeomType>
  class CoarseMinimizerKern : public MinimizerKern<DistEvalObj,GeomType> {

    public:
    
      typedef CoarseMinimizerKern<DistEvalObj,GeomType>   Type;
      
      typedef MinimizerKern<DistEvalObj,GeomType>         ParentType;

      double Step;
      
      static const uint DefaultMaxIter=20;
      
    private:
    
      void Update(const double& runStep) {
      }

  };

}

#endif

