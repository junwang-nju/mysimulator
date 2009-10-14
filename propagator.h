
#ifndef _Propagator_H_
#define _Propagator_H_

#include "monomer-propagator-format.h"

namespace std {

  enum GlobalPropagatorParamType {
    GDeltaTime=0,
    StartTime,
    TotalTime,
    OutputInterval,
    NumberOutput,
    NumberStep4OneOutput,
    NumberGPParam
  };

  template <typename DistEvalObj, typename GeomType>
  class Propagator {
    
    public:
    
      varVector<MonomerPropagatorFormat<DistEvalObj,GeomType> > MerMove;
      
      void (*SetStructure)(
          const varVector<Property>&,
          varVector<MonomerPropagatorFormat<DistEvalObj,GeomType> >&);

      void (*Step)(
          varVector<Property>&, const ParamList&,
          varVector<IDList<DistEvalObj,GeomType> >&,
          varVector<MonomerPropagatorFormat<DistEvalObj,GeomType> >&,
          DistEvalObj&, const GeomType&);

      varVector<double> GlobalPropagatorParam;
      
      void AllocStructure(const varVector<Property>& PropSet) {
        SetStructure(PropSet,MerMove);
      }
      
      void AllocParam(const uint*propdim, const uint& n) {
        GlobalPropagatorParam.allocate(static_cast<uint>(NumberGPParam));
        uint m=MerMove.size();
        for(uint i=0;i<m;++i)
          MerMove[i].alloc(MerMove[i].PropagatorParam,propdim,n);
      }

      void SetTimeStep(const double& dt) {
        GlobalPropagatorParam[GDeltaTime]=dt;
        uint n=MerMove.size();
        for(uint i=0;i<n;++i)
          MerMove[i].setfunc[0](MerMove[i].PropagatorParam,&dt,1);
      }

      void SetStartTime(const double& st) {
        GlobalPropagatorParam[StartTime]=st;
      }

      void SetTotalTime(const double& tt) {
        GlobalPropagatorParam[TotalTime]=tt;
      }

      void SetOutputTimeInterval(const double& ot) {
        GlobalPropagatorParam[OutputInterval]=ot;
      }
      
      void Synchronize(const varVector<Property>& PropSet) {
        GlobalPropagatorParam[NumberOutput]=
          GlobalPropagatorParam[TotalTime]/
          GlobalPropagatorParam[OutputInterval];
        GlobalPropagatorParam[NumberStep4OneOutput]=
          GlobalPropagatorParam[OutputInterval]/
          GlobalPropagatorParam[GDeltaTime];
        uint n=MerMove.size();
        for(uint i=0;i<n;++i)
          MerMove[i].sync(PropSet[i],MerMove[i].PropagatorParam);
      }

      void (*Output)(
          ostream&,
          const varVector<Property>&, const ParamList&,
          varVector<IDList<DistEvalObj,GeomType> >&,
          DistEvalObj&, const GeomType&);

      void Run(
          varVector<Property>& PropSet, const ParamList& PList,
          varVector<IDList<DistEvalObj,GeomType> >& IDLS,
          DistEvalObj& DEval, const GeomType& Geo,
          ostream& os=cout) {
        uint no=static_cast<int>(GlobalPropagatorParam[NumberOutput]+0.5);
        uint ns=
          static_cast<int>(GlobalPropagatorParam[NumberStep4OneOutput]+0.5);
        for(uint i=0;i<no;++i) {
          for(uint j=0;j<ns;++j)
            Step(PropSet,PList,IDLS,MerMove,DEval,Geo);
          Output(os,PropSet,PList,IDLS,DEval,Geo);
        }
      }

  };

}

#endif
