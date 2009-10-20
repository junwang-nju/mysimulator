
#ifndef _Propagator_H_
#define _Propagator_H_

#include "monomer-propagator.h"
#include "param-list.h"
#include "id-list.h"
#include "propagator-common-index.h"
#include "propagator-op.h"

namespace std {

  void AllocCommonParameter(ParamPackType& cgbPrm, const varVector<Property>&){
    PropagatorParamAllocate(cgbPrm,static_cast<uint>(NumberCommonParam));
    PropagatorParamAllocate(cgbPrm[BasicCommon],
                            static_cast<uint>(NumberBasicCommon));
  } 

  void SetTimeStep(ParamPackType& cgbPrm, const double* data,const uint&) {
    cgbPrm[BasicCommon][DeltaTime]=*data;
    cgbPrm[BasicCommon][HalfDeltaTime]=0.5*cgbPrm[BasicCommon][DeltaTime];
  }

  void SetStartTime(ParamPackType& cgbPrm, const double* data,const uint&) {
    cgbPrm[BasicCommon][StartTime]=*data;
  }

  void SetTotalTime(ParamPackType& cgbPrm, const double* data,const uint&) {
    cgbPrm[BasicCommon][TotalTime]=*data;
  }

  void SetOutputInterval(ParamPackType& cgbPrm,const double* data,const uint&){
    cgbPrm[BasicCommon][OutputInterval]=*data;
  }

  void SynchronizeCommon(ParamPackType& cgbPrm) {
    cgbPrm[BasicCommon][CountOutput]=cgbPrm[BasicCommon][TotalTime]/
                                     cgbPrm[BasicCommon][OutputInterval];
    cgbPrm[BasicCommon][CountStepInOne]=cgbPrm[BasicCommon][OutputInterval]/
                                        cgbPrm[BasicCommon][DeltaTime];
  }

  template <typename DistEvalObj, typename GeomType>
  class Propagator {

    public:
    
      typedef Propagator<DistEvalObj,GeomType>  Type;
    
      typedef varVector<MonomerPropagator>  UnitMovePackType;
      
      typedef void (*AllocFuncType)(ParamPackType&,const varVector<Property>&);

      typedef void (*SetFuncType)(ParamPackType&,const double*,const uint&);
      
      typedef void (*StepFuncType)(varVector<Property>&,const ParamList&,
                                   varVector<IDList<DistEvalObj,GeomType> >&,
                                   UnitMovePackType&, ParamPackType&,
                                   ParamPackType&,
                                   DistEvalObj&, const GeomType&);

      typedef void (*SyncFuncType)(const varVector<Property>&,
                                   UnitMovePackType&,ParamPackType&,
                                   ParamPackType&);

      typedef void (*OutputType)(ostream&, const Type&,
                                 const varVector<Property>&, const ParamList&,
                                 varVector<IDList<DistEvalObj,GeomType> >&,
                                 DistEvalObj&, const GeomType&);

      UnitMovePackType UnitMove;
      
      ParamPackType CmnGbParam;
      
      ParamPackType GbParam;
      
      AllocFuncType CmnGbAlloc;
      
      AllocFuncType GbAlloc;
      
      varVector<SetFuncType> CmnGbSetFunc;

      varVector<SetFuncType> GbSetFunc;
      
      StepFuncType Step;
      
      SyncFuncType Sync;

      void SyncAll(const varVector<Property>& PropSet, UnitMovePackType& UMP,
                   ParamPackType& gbPrm, ParamPackType& cgbPrm) {
        SynchronizeCommon(cgbPrm);
        Sync(PropSet,UMP,gbPrm,cgbPrm);
      }

      OutputType OutFunc;

      void Run(varVector<Property>& PropSet, const ParamList& PList,
               varVector<IDList<DistEvalObj,GeomType> >& IDLS,
               DistEvalObj& DEval, const GeomType& Geo, ostream& os) {
        uint no=static_cast<uint>(CmnGbParam[BasicCommon][CountOutput]+0.5);
        uint ns=static_cast<uint>(CmnGbParam[BasicCommon][CountStepInOne]+0.5);
        for(uint i=0;i<no;++i) {
          for(uint j=0;j<ns;++j)
            Step(PropSet,PList,IDLS,UnitMove,CmnGbParam,GbParam,DEval,Geo);
          OutFunc(os,*this,PropSet,PList,IDLS,DEval,Geo);
        }
      }

      Propagator() : CmnGbAlloc(AllocCommonParameter) {
        PropagatorParamAllocate(CmnGbSetFunc,
                                static_cast<uint>(NumberSetCommon));
        CmnGbSetFunc[SetCmnTimeStep]=SetTimeStep;
        CmnGbSetFunc[SetCmnStartTime]=SetStartTime;
        CmnGbSetFunc[SetCmnTotalTime]=SetTotalTime;
        CmnGbSetFunc[SetCmnOutputInterval]=SetOutputInterval;
        varVector<Property> tPropSet;
        CmnGbAlloc(CmnGbParam,tPropSet);
      }

  };

}

#endif
