
#ifndef _Minimizer_Base_H_
#define _Minimizer_Base_H_

#include "var-vector.h"
#include "property.h"
#include "param-list.h"
#include <cmath>

namespace std {

  double MinimalStep4(const varVector<Property>& PropSet) {
    uint nprop=PropSet.size();
    uint dim=PropSet[0].Coordinate.size();
    double MinStep=0, tmd;
    Property const *nowP;
    for(uint i=0;i<nprop;++i) {
      nowP=&PropSet[i];
      for(uint j=0;j<dim;++j) {
        if(fabs(nowP->Mask[j])<1e-16)  continue;
        tmd=fabs(nowP->Coordinate[j]);
        tmd=(tmd<1.0?nowP->Velocity[j]:nowP->Velocity[i]/tmd);
        MinStep+=tmd*tmd;
      }
    }
    return DRelDelta*sqrt(dim*nprop/MinStep); 
  }

  template <typename DistEvalObj, typename GeomType>
  class MinimizerKern {

    public:

      varVector<Property> runSys;

      varVector<Property> MinSys;      
      
      double              MinY;
      
      ParamList           runParam;
      
      DistEvalObj         runDEval;
      
      GeomType            runGeo;
      
      double              MinPrj;
      
      double              MinMove;
      
      uint                MinGCount;
      
      double              MinScale;
      
      MinimizerKern()
        : runSys(), MinSys(), MinY(0.), runParam(), runDEval(),
          runGeo(), MinPrj(0.), MinMove(0.), MinGCount(0), MinScale(0.1) {
      } 

      void Import(const varVector<Property>& vProp){ runSys.Duplicate(vProp); }
      
      void Import(const ParamList& PList) { runParam.Duplicate(PList); }
      
      void Import(const GeomType& Geo) { runGeo.Duplicate(Geo); }
      
      void Import(const varVector<Property>& vProp, const DistEvalObj& DEval,
                  const ParamList& PList, const GeomType& Geo,
                  const double& E) {
        Import(vProp);
        runDEval.Duplicate(DEval);
        Import(PList);
        Import(Geo);
        MinSys.Duplicate(vProp);
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
    
      void Update(const double& runStep,)

  };

}

#endif

