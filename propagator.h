
#ifndef _Propagator_H_
#define _Propagator_H_

#include "monomer-propagator.h"
#include "param-list.h"
#include "id-list.h"
#include "propagator-common-index.h"

namespace std {

  void AllocCommonParameter(ParamPackType& cgbPrm,const VectorBase<Property>&){
    cgbPrm.allocate(NumberCommonParam);
    cgbPrm[BasicCommon].allocate(NumberBasicCommon);
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
    
      typedef void (*AllocFuncType)(ParamPackType&,
                                    const VectorBase<Property>&);

      typedef void (*SetFuncType)(ParamPackType&,const double*,const uint&);
      
      typedef void (*StepFuncType)(VectorBase<Property>&,const ParamList&,
                                   VectorBase<IDList<DistEvalObj,GeomType> >&,
                                   VectorBase<MonomerPropagator>&,
                                   ParamPackType&, ParamPackType&,
                                   DistEvalObj&, const GeomType&);

      typedef void (*SyncFuncType)(const VectorBase<Property>&,
                                   VectorBase<MonomerPropagator>&,
                                   ParamPackType&,ParamPackType&);

      typedef void (*OutputType)(ostream&, const Type&,
                                 const VectorBase<Property>&, const ParamList&,
                                 VectorBase<IDList<DistEvalObj,GeomType> >&,
                                 DistEvalObj&, const GeomType&);

      varVector<MonomerPropagator> UnitMove;
      
      ParamPackType CmnGbParam;
      
      ParamPackType GbParam;
      
      AllocFuncType CmnGbAlloc;
      
      AllocFuncType GbAlloc;

      void AllocAll(const VectorBase<Property>& PropSet) {
        GbAlloc(GbParam,PropSet);
        uint n=PropSet.size();
        for(uint i=0;i<n;++i)
          UnitMove[i].Alloc(UnitMove[i].runParam,PropSet[i]);
      }

      varVector<SetFuncType> CmnGbSetFunc;

      varVector<SetFuncType> GbSetFunc;
      
      StepFuncType Step;
      
      SyncFuncType Sync;

      void SyncAll(const VectorBase<Property>& PropSet) {
        SynchronizeCommon(CmnGbParam);
        Sync(PropSet,UnitMove,GbParam,CmnGbParam);
      }

      OutputType OutFunc;

      void Run(VectorBase<Property>& PropSet, const ParamList& PList,
               VectorBase<IDList<DistEvalObj,GeomType> >& IDLS,
               DistEvalObj& DEval, const GeomType& Geo, ostream& os) {
        uint no=static_cast<uint>(CmnGbParam[BasicCommon][CountOutput]+0.5);
        uint ns=static_cast<uint>(CmnGbParam[BasicCommon][CountStepInOne]+0.5);
        double ot=ns*CmnGbParam[BasicCommon][DeltaTime];
        CmnGbParam[BasicCommon][NowTime]=CmnGbParam[BasicCommon][StartTime];
        OutFunc(os,*this,PropSet,PList,IDLS,DEval,Geo);
        for(uint i=0;i<no;++i) {
          for(uint j=0;j<ns;++j)
            Step(PropSet,PList,IDLS,UnitMove,GbParam,CmnGbParam,DEval,Geo);
          CmnGbParam[BasicCommon][NowTime]+=ot;
          OutFunc(os,*this,PropSet,PList,IDLS,DEval,Geo);
        }
      }

      Propagator() : CmnGbAlloc(AllocCommonParameter) {
        CmnGbSetFunc.allocate(NumberSetCommon);
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
