
#ifndef _Propagator_H_
#define _Propagator_H_

#include "interaction-method.h"
#include "monomer-propagator.h"
#include "monomer-propagator-op.h"
#include "propagator-parameter-name-common.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  struct Propagator {

    typedef Propagator<DistEvalMethod,GeomType> Type;
    typedef void (*GSyncFuncType)(const Vector<double>*, const Vector<double>*,
                                  const unsigned int, UniqueParameter*);
    typedef void (*GSetFuncType)(UniqueParameter*,const void*);
    typedef InteractionMethod<DistEvalMethod,GeomType>  InteractionType;
    typedef void (*FOutputFuncType)(ostream&, const Type&,InteractionType*,
                                    const Vector<double>*,const Vector<double>*,
                                    const Vector<double>*,const Vector<double>*,
                                    const Vector<unsigned int>*,
                                    const Vector<UniqueParameter>*,
                                    const unsigned int, const unsigned int,
                                    DistEvalMethod&, const GeomType&);
    typedef void (*HOutputFuncType)(ostream&, const Type&,InteractionType*,
                                    const Vector<double>*,const Vector<double>*,
                                    const Vector<double>*,const Vector<double>*,
                                    const Vector<Vector<unsigned int> >*,
                                    const Vector<Vector<UniqueParameter> >*,
                                    const unsigned int, const unsigned int,
                                    DistEvalMethod&, const GeomType&);
    typedef void (*FStepFuncType)(InteractionType*,
                                  Vector<double>*,Vector<double>*,
                                  Vector<double>*,const Vector<double>*,
                                  const Vector<unsigned int>*,
                                  const Vector<UniqueParameter>*,
                                  UniqueParameter*,MonomerPropagator*,
                                  const unsigned int, const unsigned int,
                                  DistEvalMethod&,const GeomType&);
    typedef void (*HStepFuncType)(InteractionType*,
                                  Vector<double>*,Vector<double>*,
                                  Vector<double>*,const Vector<double>*,
                                  const Vector<Vector<unsigned int> >*,
                                  const Vector<Vector<UniqueParameter> >*,
                                  UniqueParameter*,MonomerPropagator*,
                                  const unsigned int, const unsigned int,
                                  DistEvalMethod&,const GeomType&);

    unsigned int *MoveMode;
    Vector<MonomerPropagator> Unit;
    GSyncFuncType GSync;
    Vector<GSetFuncType>  GSet;
    FOutputFuncType FOutput;
    HOutputFuncType HOutput;
    FStepFuncType   FStep;
    HStepFuncType   HStep;
    Vector<UniqueParameter> GParam;
    ostream* os;
    unsigned int state;

    Propagator()
      : MoveMode(NULL), Unit(), GSync(NULL), GSet(), FOutput(NULL),
        HOutput(NULL), FStep(NULL), HStep(NULL), GParam(), os(NULL),
        state(Unused) {} 
    Propagator(const Type&) { myError("Cannot create from Propagator"); }
    Type& operator=(const Type& P) { assign(*this,P); return *this; }
    ~Propagator() { release(*this); }

  };
  
  template <typename DistEvalMethod, typename GeomType>
  bool IsAvailable(const Propagator<DistEvalMethod,GeomType>& P) {
    return IsAvailable(P.MoveMode);
  }

  template <typename DistEvalMethod, typename GeomType>
  void release(Propagator<DistEvalMethod,GeomType>& P) {
    if(P.state==Allocated)  safe_delete(P.MoveMode);
    else P.MoveMode=NULL;
    release(P.Unit);
    P.GSync=NULL;
    release(P.GSet);
    P.FOutput=NULL;
    P.HOutput=NULL;
    P.FStep=NULL;
    P.HStep=NULL;
    release(P.GParam);
    P.os=NULL;
    P.state=Unused;
  }

  template <typename DistEvalMethod, typename GeomType>
  void allocate(Propagator<DistEvalMethod,GeomType>& P) {
    release(P);
    P.MoveMode=new unsigned int;
    P.os=&cout;
    P.state=Allocated;
  }

  template <typename DistEvalMethod, typename GeomType>
  void assign(Propagator<DistEvalMethod,GeomType>& dest,
              const Propagator<DistEvalMethod,GeomType>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    if(*(dest.MoveMode)!=*(src.MoveMode)) {
      release(dest);
      allocate(dest);
      if(IsAvailable(src.Unit)) {
        allocate(dest.Unit,src.Unit.size);
        for(unsigned int i=0;i<dest.Unit.size;++i) {
          allocate(dest.Unit[i]);
          Set(dest.Unit[i],*(src.Unit[i].UnitKind),*(src.MoveMode));
        }
      }
      if(IsAvailable(src.GSet))   allocate(dest.GSet,src.GSet.size);
      if(IsAvailable(src.GParam)) allocate(dest.GParam,src.GParam.size);
    }
    *(dest.MoveMode)=*(src.MoveMode);
    if(IsAvailable(src.Unit))   assign(dest.Unit,src.Unit);
    dest.GSync=src.GSync;
    if(IsAvailable(src.GSet))   assign(dest.GSet,src.GSet);
    dest.FOutput=src.FOutput;
    dest.HOutput=src.HOutput;
    dest.FStep=src.FStep;
    dest.HStep=src.HStep;
    dest.os=src.os;
    if(IsAvailable(src.GParam)) assign(dest.GParam,src.GParam);
  }

  template <typename DistEvalMethod, typename GeomType>
  void refer(Propagator<DistEvalMethod,GeomType>& dest,
             const Propagator<DistEvalMethod,GeomType>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.MoveMode=src.MoveMode;
    refer(dest.Unit,src.Unit);
    dest.GSync=src.GSync;
    refer(dest.GSet,src.GSet);
    dest.FOutput=src.FOutput;
    dest.HOutput=src.HOutput;
    dest.FStep=src.FStep;
    dest.HStep=src.HStep;
    refer(dest.GParam,src.GParam);
    dest.os=src.os;
    dest.state=Reference;
  }

  template <typename DistEvalMethod, typename GeomType>
  void synchronize(Propagator<DistEvalMethod,GeomType>& P,
                   const Vector<double>* ivMass, const Vector<double>* dMask,
                   const unsigned int nunit) {
    P.GParam[CountOutput].u=
        static_cast<unsigned int>(P.GParam[TotalTime].d/
                                  P.GParam[OutputInterval].d);
    P.GParam[CountStepInOneOutput].u=
        static_cast<unsigned int>(P.GParam[OutputInterval].d/
                                  P.GParam[DeltaTime].d);
    P.GSync(ivMass,dMask,nunit,P.GParam());
    for(unsigned int i=0;i<P.Unit.size;++i)
      synchronize(P.Unit[i],ivMass[i],P.GParam());
  }

  template <typename DistEvalMethod,typename GeomType, typename T>
  void setparameter(Propagator<DistEvalMethod,GeomType>& P,
                    const unsigned int ComponentID, const T& d) {
    P.GSet[ComponentID](P.GParam,reinterpret_cast<const void*>(&d));
  }

  template <typename DistEvalMethod, typename GeomType>
  void buildUnit(Propagator<DistEvalMethod,GeomType>& P,
                 const unsigned int MType,
                 const unsigned int* UType, const unsigned int nunit) {
    allocate(P.Unit,nunit);
    for(unsigned int i=0;i<nunit;++i) {
      allocate(P.Unit[i]);
      Set(P.Unit[i],UType[i],MType);
    }
  }

  template <typename DistEvalMethod, typename GeomType>
  void Write(const Propagator<DistEvalMethod,GeomType>& P, 
             InteractionMethod<DistEvalMethod,GeomType>* IMLst,
             const Vector<double>* Coor, const Vector<double>* Vel,
             const Vector<double>* Grad, const Vector<double>* Mass,
             const Vector<unsigned int>* IdxLst,
             const Vector<UniqueParameter>* PrmLst,
             const unsigned int nunit, const unsigned int nlst,
             DistEvalMethod& DEval, const GeomType& Geo) {
    P.FOutput(*(P.os),P,IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,
              nunit,nlst,DEval,Geo);
  }
  
  template <typename DistEvalMethod, typename GeomType>
  void Write(const Propagator<DistEvalMethod,GeomType>& P, 
             InteractionMethod<DistEvalMethod,GeomType>* IMLst,
             const Vector<double>* Coor, const Vector<double>* Vel,
             const Vector<double>* Grad, const Vector<double>* Mass,
             const Vector<Vector<unsigned int> >* IdxLst,
             const Vector<Vector<UniqueParameter> >* PrmLst,
             const unsigned int nunit, const unsigned int nlst,
             DistEvalMethod& DEval, const GeomType& Geo) {
    P.HOutput(*(P.os),P,IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,
              nunit,nlst,DEval,Geo);
  }

  template <typename DistEvalMethod, typename GeomType>
  void Step(Propagator<DistEvalMethod,GeomType>& P,
            InteractionMethod<DistEvalMethod,GeomType>* IMLst,
            Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
            const Vector<double>* Mass, const Vector<unsigned int>* IdxLst,
            const Vector<UniqueParameter>* PrmLst,
            const unsigned int nunit, const unsigned int nlst,
            DistEvalMethod& DEval, const GeomType& Geo) {
    P.FStep(IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,P.GParam(),P.Unit(),
            nunit,nlst,DEval,Geo);
  }

  template <typename DistEvalMethod, typename GeomType>
  void Step(Propagator<DistEvalMethod,GeomType>& P,
            InteractionMethod<DistEvalMethod,GeomType>* IMLst,
            Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
            const Vector<double>* Mass,
            const Vector<Vector<unsigned int> >* IdxLst,
            const Vector<Vector<UniqueParameter> >* PrmLst,
            const unsigned int nunit, const unsigned int nlst,
            DistEvalMethod& DEval, const GeomType& Geo) {
    P.HStep(IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,P.GParam(),P.Unit(),
            nunit,nlst,DEval,Geo);
  }

  template <typename DistEvalMethod, typename GeomType>
  void Run(Propagator<DistEvalMethod,GeomType>& P,
           Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
           const Vector<double>* Mass,
           InteractionMethod<DistEvalMethod,GeomType>* IMLst,
           const Vector<unsigned int>* IdxLst,
           const Vector<UniqueParameter>* PrmLst,
           const unsigned int nunit, const unsigned int nlst,
           DistEvalMethod& DEval, const GeomType& Geo) {
    unsigned int no=P.GParam[CountOutput].u;
    unsigned int ns=P.GParam[CountStepInOneOutput].u;
    double ot=ns*P.GParam[DeltaTime].d;
    P.GParam[NowTime]=P.GParam[StartTime];
    Write(P,IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,nunit,nlst,DEval,Geo);
    for(unsigned int i=0;i<no;++i) {
      for(unsigned int j=0;j<ns;++j)
        Step(P,IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,nunit,nlst,DEval,Geo);
      P.GParam[NowTime].d+=ot;
      Write(P,IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,nunit,nlst,DEval,Geo);
    }
  }

  template <typename DistEvalMethod, typename GeomType>
  void Run(Propagator<DistEvalMethod,GeomType>& P,
           Vector<double>* Coor, Vector<double>* Vel, Vector<double>* Grad,
           const Vector<double>* Mass,
           InteractionMethod<DistEvalMethod,GeomType>* IMLst,
           const Vector<Vector<unsigned int> >* IdxLst,
           const Vector<Vector<UniqueParameter> >* PrmLst,
           const unsigned int nunit, const unsigned int nlst,
           DistEvalMethod& DEval, const GeomType& Geo) {
    unsigned int no=P.GParam[CountOutput].u;
    unsigned int ns=P.GParam[CountStepInOneOutput].u;
    double ot=ns*P.GParam[DeltaTime].d;
    P.GParam[NowTime]=P.GParam[StartTime];
    Write(P,IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,nunit,nlst,DEval,Geo);
    for(unsigned int i=0;i<no;++i) {
      for(unsigned int j=0;j<ns;++j)
        Step(P,IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,nunit,nlst,DEval,Geo);
      P.GParam[NowTime].d+=ot;
      Write(P,IMLst,Coor,Vel,Grad,Mass,IdxLst,PrmLst,nunit,nlst,DEval,Geo);
    }
  }

}

#endif

