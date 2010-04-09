
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
          VectorBase<PropagatorDataElementType>&);

      typedef InteractionMethod<DistEvalMethod,GeomType>  InteractionType;

      typedef void (*GSetFuncType)(
          VectorBase<PropagatorDataElementType>&, const void*);

      typedef void (*FOutputFuncTypeVarVar)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<unsigned int> >&,
          const VectorBase<refVector<double> >&,
          DistEvalMethod<varVector>&, const GeomType<varVector>&);

      typedef void (*FOutputFuncTypeVarRef)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<unsigned int> >&,
          const VectorBase<refVector<double> >&,
          DistEvalMethod<varVector>&, const GeomType<refVector>&);

      typedef void (*FOutputFuncTypeRefVar)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<unsigned int> >&,
          const VectorBase<refVector<double> >&,
          DistEvalMethod<refVector>&, const GeomType<varVector>&);

      typedef void (*FOutputFuncTypeRefRef)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<unsigned int> >&,
          const VectorBase<refVector<double> >&,
          DistEvalMethod<refVector>&, const GeomType<refVector>&);

      typedef void (*HOutputFuncTypeVarVar)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<refVector<unsigned int> > >&,
          const VectorBase<refVector<refVector<double> > >&,
          DistEvalMethod<varVector>&, const GeomType<varVector>&);

      typedef void (*HOutputFuncTypeVarRef)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<refVector<unsigned int> > >&,
          const VectorBase<refVector<refVector<double> > >&,
          DistEvalMethod<varVector>&, const GeomType<refVector>&);

      typedef void (*HOutputFuncTypeRefVar)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<refVector<unsigned int> > >&,
          const VectorBase<refVector<refVector<double> > >&,
          DistEvalMethod<refVector>&, const GeomType<varVector>&);

      typedef void (*HOutputFuncTypeRefRef)(
          ostream&, const Type&, const VectorBase<InteractionType>&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<double> >&,
          const VectorBase<refVector<refVector<unsigned int> > >&,
          const VectorBase<refVector<refVector<double> > >&,
          DistEvalMethod<refVector>&, const GeomType<refVector>&);

      typedef void (*FStepFuncTypeVarVar)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<double> >&, 
          const VectorBase<refVector<unsigned int> >&, 
          const VectorBase<refVector<double> >&, 
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<varVector>&, const GeomType<varVector>&);

      typedef void (*FStepFuncTypeVarRef)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<double> >&, 
          const VectorBase<refVector<unsigned int> >&, 
          const VectorBase<refVector<double> >&,
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<varVector>&, const GeomType<refVector>&);

      typedef void (*FStepFuncTypeRefVar)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<double> >&, 
          const VectorBase<refVector<unsigned int> >&, 
          const VectorBase<refVector<double> >&,
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<refVector>&, const GeomType<varVector>&);

      typedef void (*FStepFuncTypeRefRef)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<double> >&, 
          const VectorBase<refVector<unsigned int> >&, 
          const VectorBase<refVector<double> >&,
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<refVector>&, const GeomType<refVector>&);

      typedef void (*HStepFuncTypeVarVar)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<double> >&, 
          const VectorBase<refVector<refVector<unsigned int> > >&, 
          const VectorBase<refVector<refVector<double> > >&, 
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<varVector>&, const GeomType<varVector>&);

      typedef void (*HStepFuncTypeVarRef)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<double> >&, 
          const VectorBase<refVector<refVector<unsigned int> > >&, 
          const VectorBase<refVector<refVector<double> > >&, 
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<varVector>&, const GeomType<refVector>&);

      typedef void (*HStepFuncTypeRefVar)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<double> >&, 
          const VectorBase<refVector<refVector<unsigned int> > >&, 
          const VectorBase<refVector<refVector<double> > >&, 
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<refVector>&, const GeomType<varVector>&);

      typedef void (*HStepFuncTypeRefRef)(
          const VectorBase<InteractionType>&, VectorBase<refVector<double> >&,
          VectorBase<refVector<double> >&, VectorBase<refVector<double> >&, 
          const VectorBase<refVector<double> >&, 
          const VectorBase<refVector<refVector<unsigned int> > >&, 
          const VectorBase<refVector<refVector<double> > >&, 
          VectorBase<PropagatorDataElementType>&,
          VectorBase<MonomerPropagator>& Unit,
          DistEvalMethod<refVector>&, const GeomType<refVector>&);

      unsigned int MoveMode;

      varVector<MonomerPropagator> Unit;

      GAllocFuncType  GAlloc;

      GSyncFuncType   GSync;

      varVector<GSetFuncType> GSet;

      FOutputFuncTypeVarVar  FWriteOutVV;
      FOutputFuncTypeVarRef  FWriteOutVR;
      FOutputFuncTypeRefVar  FWriteOutRV;
      FOutputFuncTypeRefRef  FWriteOutRR;
      HOutputFuncTypeVarVar  HWriteOutVV;
      HOutputFuncTypeVarRef  HWriteOutVR;
      HOutputFuncTypeRefVar  HWriteOutRV;
      HOutputFuncTypeRefRef  HWriteOutRR;

      FStepFuncTypeVarVar  FStepVV;
      FStepFuncTypeVarRef  FStepVR;
      FStepFuncTypeRefVar  FStepRV;
      FStepFuncTypeRefRef  FStepRR;
      HStepFuncTypeVarVar  HStepVV;
      HStepFuncTypeVarRef  HStepVR;
      HStepFuncTypeRefVar  HStepRV;
      HStepFuncTypeRefRef  HStepRR;

      varVector<PropagatorDataElementType> GlobalParam;

      Propagator()
        : Unit(), GAlloc(NULL), GSync(NULL), GSet(), FWriteOutVV(NULL),
          FWriteOutVR(NULL), FWriteOutRV(NULL), FWriteOutRR(NULL),
          HWriteOutVV(NULL), HWriteOutVR(NULL), HWriteOutRV(NULL),
          HWriteOutRR(NULL), FStepVV(NULL), FStepVR(NULL), FStepRV(NULL),
          FStepRR(NULL), HStepVV(NULL), HStepVR(NULL), HStepRV(NULL),
          HStepRR(NULL), GlobalParam() {
      }

      Propagator(const Type& P) { myError("Cannt create from Propagator"); }

      Type& operator=(const Type& P) {
        MoveMode=P.MoveMode;
        Unit.duplicate(P.Unit);
        GAlloc=P.GAlloc;
        GSync=P.GSync;
        GSet.duplicate(P.GSet);
        FWriteOutVV=P.FWriteOutVV;
        FWriteOutVR=P.FWriteOutVR;
        FWriteOutRV=P.FWriteOutRV;
        FWriteOutRR=P.FWriteOutRR;
        HWriteOutVV=P.HWriteOutVV;
        HWriteOutVR=P.HWriteOutVR;
        HWriteOutRV=P.HWriteOutRV;
        HWriteOutRR=P.HWriteOutRR;
        FStepVV=P.FStepVV;
        FStepVR=P.FStepVR;
        FStepRV=P.FStepRV;
        FStepRR=P.FStepRR;
        HStepVV=P.HStepVV;
        HStepVR=P.HStepVR;
        HStepRV=P.HStepRV;
        HStepRR=P.HStepRR;
        GlobalParam.duplicate(P.GlobalParam);
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
            =GlobalParam[TotalTime].d/GlobalParam[OutputInterval].d;
        GlobalParam[CountStepInOne]
            =GlobalParam[OutputInterval].d/GlobalParam[DeltaTime].d;
        GSync(IvMass.Structure(),DMask.Structure(),GlobalParam);
        for(unsigned int i=0;i<Unit.size();++i)
          Unit[i].synchronize(IvMass,GlobalParam);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo) {
        FWriteOutVV(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo) {
        FWriteOutVR(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo) {
        FWriteOutRV(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo) {
        FWriteOutRR(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
          const VectorBase<refVector<refVector<double> > >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo) {
        HWriteOutVV(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
          const VectorBase<refVector<refVector<double> > >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo) {
        HWriteOutVR(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
          const VectorBase<refVector<refVector<double> > >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo) {
        HWriteOutRV(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void WriteOut(
          ostream& os, const VectorBase<InteractionType>& IM,
          const VectorBase<refVector<double> >& Coor,
          const VectorBase<refVector<double> >& Vel,
          const VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
          const VectorBase<refVector<refVector<double> > >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo) {
        HWriteOutRR(os,*this,IM,Coor,Vel,Grad,IdxLst,ParamLst,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<double> >& Mass,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo) {
        FStepVV(IM,Coor,Vel,Grad,Mass,IdxLst,ParamLst,
                GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<double> >& Mass,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo) {
        FStepVR(IM,Coor,Vel,Grad,Mass,IdxLst,ParamLst,
                GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<double> >& Mass,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo) {
        FStepRV(IM,Coor,Vel,Grad,Mass,IdxLst,ParamLst,
                GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<double> >& Mass,
          const VectorBase<refVector<unsigned int> >& IdxLst,
          const VectorBase<refVector<double> >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo) {
        FStepRR(IM,Coor,Vel,Grad,Mass,IdxLst,ParamLst,
                GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<double> >& Mass,
          const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
          const VectorBase<refVector<refVector<double> > >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<varVector>& Geo) {
        HStepVV(IM,Coor,Vel,Grad,Mass,IdxLst,ParamLst,
                GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<double> >& Mass,
          const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
          const VectorBase<refVector<refVector<double> > >& ParamLst,
          DistEvalMethod<varVector>& DEval, const GeomType<refVector>& Geo) {
        HStepVR(IM,Coor,Vel,Grad,Mass,IdxLst,ParamLst,
                GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<double> >& Mass,
          const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
          const VectorBase<refVector<refVector<double> > >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<varVector>& Geo) {
        HStepRV(IM,Coor,Vel,Grad,Mass,IdxLst,ParamLst,
                GlobalParam,Unit,DEval,Geo);
      }

      void Step(
          const VectorBase<InteractionType>& IM,
          VectorBase<refVector<double> >& Coor,
          VectorBase<refVector<double> >& Vel,
          VectorBase<refVector<double> >& Grad,
          const VectorBase<refVector<double> >& Mass,
          const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
          const VectorBase<refVector<refVector<double> > >& ParamLst,
          DistEvalMethod<refVector>& DEval, const GeomType<refVector>& Geo) {
        HStepRR(IM,Coor,Vel,Grad,Mass,IdxLst,ParamLst,
                GlobalParam,Unit,DEval,Geo);
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
        no=static_cast<unsigned int>(GlobalParam[CountOutput].d+0.5);
        ns=static_cast<unsigned int>(GlobalParam[CountStepInOne].d+0.5);
        double ot=ns*GlobalParam[DeltaTime].d;
        GlobalParam[NowTime]=GlobalParam[StartTime];
        WriteOut(os,IM,Coordinate.Structure(),Velocity.Structure(),
                 Gradient.Structure(),IdxLst.Structure(),ParamLst,DEval,Geo);
        for(unsigned int i=0;i<no;++i) {
          for(unsigned int j=0;j<ns;++j)
            Step(IM,Coordinate.Structure(),Velocity.Structure(),
                 Gradient.Structure(),Mass.Structure(),
                 IdxLst.Structure(),ParamLst,DEval,Geo);
          GlobalParam[NowTime].d+=ot;
          WriteOut(os,IM,Coordinate.Structure(),Velocity.Structure(),
                   Gradient.Structure(),IdxLst.Structure(),ParamLst,DEval,Geo);
        }
      }

      template <template <typename> class VecTypeC,
                template <typename> class VecTypeV,
                template <typename> class VecTypeF,
                template <typename> class VecTypeM,
                template <typename> class VecTypeI,
                template <typename> class VecTypeP,
                template <typename> class VecTypeD,
                template <typename> class VecTypeG>
      void Run(PropertyList<double,VecTypeC>& Coordinate,
               PropertyList<double,VecTypeV>& Velocity,
               PropertyList<double,VecTypeF>& Gradient,
               const PropertyList<double,VecTypeM>& Mass,
               const VectorBase<InteractionType>& IM,
               const PropertyList<refVector<unsigned int>,VecTypeI>& IdxLst,
               const PropertyList<refVector<double>,VecTypeP>& ParamLst,
               DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
               ostream& os) {
        unsigned int no,ns;
        no=static_cast<unsigned int>(GlobalParam[CountOutput].d+0.5);
        ns=static_cast<unsigned int>(GlobalParam[CountStepInOne].d+0.5);
        double ot=ns*GlobalParam[DeltaTime].d;
        GlobalParam[NowTime]=GlobalParam[StartTime];
        WriteOut(os,IM,Coordinate.Structure(),Velocity.Structure(),
                 Gradient.Structure(),IdxLst.Structure(),
                 ParamLst.Structure(),DEval,Geo);
        for(unsigned int i=0;i<no;++i) {
          for(unsigned int j=0;j<ns;++j)
            Step(IM,Coordinate.Structure(),Velocity.Structure(),
                 Gradient.Structure(),Mass.Structure(),IdxLst.Structure(),
                 ParamLst.Structure(),DEval,Geo);
          GlobalParam[NowTime].d+=ot;
          WriteOut(os,IM,Coordinate.Structure(),Velocity.Structure(),
                   Gradient.Structure(),IdxLst.Structure(),
                   ParamLst.Structure(),DEval,Geo);
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

#include "propagator-op.h"

#endif

