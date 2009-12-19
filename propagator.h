
#ifndef _Propagator_H_
#define _Propagator_H_

#include "monomer-propagator.h"
#include "param-list.h"
#include "interaction-list.h"
#include "propagator-common-index.h"

namespace std {

  void AllocCommonParameter(FuncParamType& cgbPrm){
    cgbPrm.allocate(NumberCommonParam);
    varVector<uint> offset(NumberCommonParam),size(NumberCommonParam);
    offset[BasicCommon]=0;    size[BasicCommon]=NumberBasicCommon;
    cgbPrm.BuildStructure(offset,size);
  } 

  void SetTimeStep(FuncParamType& cgbPrm, const double* data,const uint&) {
    cgbPrm[BasicCommon][DeltaTime]=*data;
    cgbPrm[BasicCommon][HalfDeltaTime]=0.5*cgbPrm[BasicCommon][DeltaTime];
  }

  void SetStartTime(FuncParamType& cgbPrm, const double* data,const uint&) {
    cgbPrm[BasicCommon][StartTime]=*data;
  }

  void SetTotalTime(FuncParamType& cgbPrm, const double* data,const uint&) {
    cgbPrm[BasicCommon][TotalTime]=*data;
  }

  void SetOutputInterval(FuncParamType& cgbPrm,const double* data,const uint&){
    cgbPrm[BasicCommon][OutputInterval]=*data;
  }

  void SynchronizeCommon(FuncParamType& cgbPrm) {
    cgbPrm[BasicCommon][CountOutput]=cgbPrm[BasicCommon][TotalTime]/
                                     cgbPrm[BasicCommon][OutputInterval];
    cgbPrm[BasicCommon][CountStepInOne]=cgbPrm[BasicCommon][OutputInterval]/
                                        cgbPrm[BasicCommon][DeltaTime];
  }

  template <typename DistEvalObj, typename GeomType>
  class Propagator {

    public:
    
      typedef Propagator<DistEvalObj,GeomType>  Type;
    
      typedef void (*AllocFuncType)(FuncParamType&);

      typedef void (*SetFuncType)(FuncParamType&,const double*,const uint&);
      
      typedef void (*StepFuncType)(VectorBase<refVector<double> >&,
                                   VectorBase<refVector<double> >&,
                                   VectorBase<refVector<double> >&,
                                   const VectorBase<refVector<double> >&,
                                   const ParamList&,
                                   VectorBase<IDList<DistEvalObj,GeomType> >&,
                                   VectorBase<MonomerPropagator>&,
                                   FuncParamType&, FuncParamType&,
                                   DistEvalObj&, const GeomType&);

      typedef void (*SyncFuncType)(const VectorBase<refVector<double> >&,
                                   const VectorBase<refVector<double> >&,
                                   FuncParamType&,FuncParamType&,
                                   VectorBase<MonomerPropagator>&);

      typedef void (*OutputType)(ostream&, const Type&,
                                 const VectorBase<refVector<double> >&,
                                 const VectorBase<refVector<double> >&,
                                 const VectorBase<refVector<double> >&,
                                 const ParamList&,
                                 VectorBase<IDList<DistEvalObj,GeomType> >&,
                                 DistEvalObj&, const GeomType&);

      varVector<MonomerPropagator> UnitMove;
      
      FuncParamType CmnGbParam;
      
      FuncParamType GbParam;
      
      AllocFuncType CmnGbAlloc;
      
      AllocFuncType GbAlloc;

      void AllocAll(const VectorBase<refVector<uint> >& SizeInf) {
        uint n=SizeInf.size();
        assert(n==UnitMove.size());
        GbAlloc(GbParam);
        for(uint i=0;i<n;++i)
          UnitMove[i].Alloc(UnitMove[i].runParam,SizeInf[i]);
      }

      varVector<SetFuncType> CmnGbSetFunc;

      varVector<SetFuncType> GbSetFunc;
      
      StepFuncType Step;
      
      SyncFuncType Sync;

      void SyncAll(const VectorBase<refVector<double> >& IvMass) {
        SynchronizeCommon(CmnGbParam);
        Sync(IvMass,GbParam,CmnGbParam,UnitMove);
      }

      OutputType OutFunc;

      void Run(VectorBase<refVector<double> >& Coordinate,
               VectorBase<refVector<double> >& Velocity,
               VectorBase<refVector<double> >& Gradient,
               const VectorBase<refVector<double> >& Mass,
               const ParamList& PList,
               VectorBase<IDList<DistEvalObj,GeomType> >& IDLS,
               DistEvalObj& DEval, const GeomType& Geo, ostream& os) {
        uint no=static_cast<uint>(CmnGbParam[BasicCommon][CountOutput]+0.5);
        uint ns=static_cast<uint>(CmnGbParam[BasicCommon][CountStepInOne]+0.5);
        double ot=ns*CmnGbParam[BasicCommon][DeltaTime];
        CmnGbParam[BasicCommon][NowTime]=CmnGbParam[BasicCommon][StartTime];
        OutFunc(os,*this,Coordinate,Velocity,Gradient,PList,IDLS,DEval,Geo);
        for(uint i=0;i<no;++i) {
          for(uint j=0;j<ns;++j)
            Step(Coordinate,Velocity,Gradient,Mass,PList,IDLS,UnitMove,
                 GbParam,CmnGbParam,DEval,Geo);
          CmnGbParam[BasicCommon][NowTime]+=ot;
          OutFunc(os,*this,Coordinate,Velocity,Gradient,PList,IDLS,DEval,Geo);
        }
      }

      Propagator() : CmnGbAlloc(AllocCommonParameter) {
        CmnGbSetFunc.allocate(NumberSetCommon);
        CmnGbSetFunc[SetCmnTimeStep]=SetTimeStep;
        CmnGbSetFunc[SetCmnStartTime]=SetStartTime;
        CmnGbSetFunc[SetCmnTotalTime]=SetTotalTime;
        CmnGbSetFunc[SetCmnOutputInterval]=SetOutputInterval;
        CmnGbAlloc(CmnGbParam);
      }

  };

}

#endif
