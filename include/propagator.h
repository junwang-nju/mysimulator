
#ifndef _Propagator_H_
#define _Propagator_H_

#include "monomer-propagator.h"
#include "property-list.h"
#include "interaction-method.h"
#include "propagator-parameter-name-common.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  class Propagator;

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void SetUp(Propagator<DistEvalMethod,GeomType>&, const unsigned int);

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  class Propagator {

    public:

      typedef Propagator<DistEvalMethod,GeomType>   Type;

      typedef void (*GAllocFuncType)(varVector<PropagatorDataElementType>&);

      typedef void (*GSyncFuncType)(
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>&);

      typedef InteractionMethod<DistEvalMethod,GeomType>  InteractionType;

      typedef void (*OutputFuncTypeVarVar)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<unsigned int> >&,
          const VectorBase<refVector<double> >&,
          DistEvalMethod<varVector>&, const GeomType<varVector>&);

      typedef void (*OutputFuncTypeVarRef)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<unsigned int> >&,
          const VectorBase<refVector<double> >&,
          DistEvalMethod<varVector>&, const GeomType<refVector>&);

      typedef void (*OutputFuncTypeRefVar)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<unsigned int> >&,
          const VectorBase<refVector<double> >&,
          DistEvalMethod<refVector>&, const GeomType<varVector>&);

      typedef void (*OutputFuncTypeRefRef)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<unsigned int> >&,
          const VectorBase<refVector<double> >&,
          DistEvalMethod<refVector>&, const GeomType<refVector>&);

      typedef void (*StepFuncTypeVarVar)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<unsigned int> >&, 
          const VectorBase<refVector<double> >&, 
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<varVector>&, const GeomType<varVector>&);

      typedef void (*StepFuncTypeVarRef)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<unsigned int> >&, 
          const VectorBase<refVector<double> >&,
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<varVector>&, const GeomType<refVector>&);

      typedef void (*StepFuncTypeRefVar)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<unsigned int> >&, 
          const VectorBase<refVector<double> >&,
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<refVector>&, const GeomType<varVector>&);

      typedef void (*StepFuncTypeRefRef)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<unsigned int> >&, 
          const VectorBase<refVector<double> >&,
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<refVector>&, const GeomType<refVector>&);

      unsigned int MoveMode;

      varVector<MonomerPropagator> Unit;

      GAllocFuncType  GAlloc;

      GSyncFuncType   GSync;

      OutputFuncTypeVarVar  WriteOutVV;
      OutputFuncTypeVarRef  WriteOutVR;
      OutputFuncTypeRefVar  WriteOutRV;
      OutputFuncTypeRefRef  WriteOutRR;

      StepFuncTypeVarVar  StepVV;
      StepFuncTypeVarRef  StepVR;
      StepFuncTypeRefVar  StepRV;
      StepFuncTypeRefRef  StepRR;

      varVector<double> GlobalParam;

      Propagator()
        : Unit(), GAlloc(NULL), GSync(NULL), WriteOutVV(NULL),
          WriteOutVR(NULL), WriteOutRV(NULL), WriteOutRR(NULL), StepVV(NULL),
          StepVR(NULL), StepRV(NULL), StepRR(NULL), GlobalParam() {
      }

      Propagator(const Type& P) { myError("Cannt create from Propagator"); }

      Type& operator=(const Type& P) {
        Unit=P.Unit;
        GAlloc=P.GAlloc;
        GSync=P.GSync;
        WriteOutVV=P.WriteOutVV;
        WriteOutVR=P.WriteOutVR;
        WriteOutRV=P.WriteOutRV;
        WriteOutRR=P.WriteOutRR;
        StepVV=P.StepVV;
        StepVR=P.StepVR;
        StepRV=P.StepRV;
        StepRR=P.StepRR;
        GlobalParam=P.GlobalParam;
        return *this;
      }

      void allocate(const unsigned int MoveType,
                    const VectorBase<unsigned int>& upMode) {
        SetUp(*this,MoveType);
        GAlloc(GlobalParam);
        Unit.allocate(upMode.size());
        for(unsigned int i=0;i<Unit.size();++i)
          Unit[i].allocate(upMode[i],MoveType);
      }

      template <template <typename> class VecTypeM,
                template <typename> class VecTypeD>
      void synchronize(const PropertyList<double,VecTypeM>& IvMass,
                       const PropertyList<double,VecTypeD>& DMask) {
        GlobalParam[CountOutput]
            =GlobalParam[TotalTime]/GlobalParam[OutputInterval];
        GlobalParam[CountStepInOne]
            =GlobalParam[OutputInterval]/GlobalParam[DeltaTime];
        GSync(IvMass.Structure(),DMask.Structure(),GlobalParam,Unit);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo) {
        WriteOutVV(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo) {
        WriteOutVR(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo) {
        WriteOutRV(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo) {
        WriteOutRR(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo) {
        StepVV(IM,Coor,Vel,Grad,IdxLst,ParamLst,GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo) {
        StepVR(IM,Coor,Vel,Grad,IdxLst,ParamLst,GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo) {
        StepRV(IM,Coor,Vel,Grad,IdxLst,ParamLst,GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo) {
        StepRR(IM,Coor,Vel,Grad,IdxLst,ParamLst,GlobalParam,Unit,DEval,Geo);
      }

      template <template <typename> class VecTypeC,
                template <typename> class VecTypeV,
                template <typename> class VecTypeF,
                template <typename> class VecTypeM,
                template <typename> class VecTypeI,
                template <typename> class VecTypeD,
                template <typename> class VecTypeG>
      void Run(PropertyList<double,VecTypeC>& Coordinate,
               PropertyList<double,VecTypeV>& Velocity,
               PropertyList<double,VecTypeF>& Gradient,
               const PropertyList<double,VecTypeM>& Mass,
               const VectorBase<InteractionType>& IM,
               const PropertyList<unsigned int,VecTypeI>& IdxLst,
               const VectorBase<refVector<double> >& ParamLst,
               DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
               ostream& os) {
        unsigned int no,ns;
        no=static_cast<unsigned int>(GlobalParam[CountOutput]+0.5);
        ns=static_cast<unsigned int>(GlobalParam[CountStepInOne]+0.5);
        double ot=ns*GlobalParam[DeltaTime];
        GlobalParam[NowTime]=GlobalParam[StartTime];
        WriteOut(os,IM,Coordinate.Structure(),Velocity.Structure(),
                 Gradient.Structure(),IdxLst.Structure(),ParamLst,DEval,Geo);
        for(unsigned int i=0;i<no;++i) {
          for(unsigned int j=0;j<ns;++j)
            Step(IM,Coordinate.Structure(),Velocity.Structure(),
                 Gradient.Structure(),IdxLst.Structure(),ParamLst,DEval,Geo);
          GlobalParam[NowTime]+=ot;
          WriteOut(os,IM,Coordinate.Structure(),Velocity.Structure(),
                   Gradient.Structure(),IdxLst.Structure(),ParamLst,DEval,Geo);
        }
      }

      void SetTimeStep(const double dt) {
        GlobalParam[DeltaTime]=dt;
        GlobalParam[HalfDeltaTime]=0.5*dt;
      }

      void SetStartTime(const double st) { GlobalParam[StartTime]=st; }

      void SetTotalTime(const double tt) { GlobalParam[TotalTime]=tt; }

      void SetOutputInterval(const double odt) {
        GlobalParam[OutputInterval]=odt;
      }

  };

}

#endif

