
#include "propagator.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include "propagator-parameter-name-common.h"
#include <iostream>
using namespace std;

void sync(const Vector<double>*,const Vector<double>*,const Vector<double>*,
          const unsigned int,UniqueParameter*) { cout<<"in Sync"<<endl; }
void msync(const Vector<double>&, const UniqueParameter*,UniqueParameter*) {
  cout<<"in msync"<<endl;
}
void seta(UniqueParameter*,const void*) { cout<<"set A"<<endl; }
void setb(UniqueParameter*,const void*) { cout<<"set B"<<endl; }

void out(ostream& os,const Propagator<DistanceEvalDirect,FreeSpace>&,
         InteractionMethod<DistanceEvalDirect,FreeSpace>*,
         const Vector<double>*,const Vector<double>*,const Vector<double>*,
         const Vector<double>*,const Vector<double>*,
         const Vector<unsigned int>*,
         const Vector<UniqueParameter>*,const unsigned int,const unsigned int,
         DistanceEvalDirect&,const FreeSpace&) {
  os<<"Out Flat"<<endl;
}
void out(ostream& os,const Propagator<DistanceEvalDirect,FreeSpace>&,
         InteractionMethod<DistanceEvalDirect,FreeSpace>*,
         const Vector<double>*,const Vector<double>*,const Vector<double>*,
         const Vector<double>*,const Vector<double>*,
         const Vector<Vector<unsigned int> >*,
         const Vector<Vector<UniqueParameter> >*,
         const unsigned int,const unsigned int,
         DistanceEvalDirect&,const FreeSpace&) {
  os<<"Out Hierarchy"<<endl;
}
void step(InteractionMethod<DistanceEvalDirect,FreeSpace>*,Vector<double>*,
          Vector<double>*,Vector<double>*,const Vector<double>*,
          const Vector<double>*,
          const Vector<unsigned int>*,const Vector<UniqueParameter>*,
          UniqueParameter*,MonomerPropagator*,const unsigned int,
          const unsigned int,DistanceEvalDirect&,const FreeSpace&) {
  cout<<"step flat"<<endl;
}
void step(InteractionMethod<DistanceEvalDirect,FreeSpace>*,Vector<double>*,
          Vector<double>*,Vector<double>*,const Vector<double>*,
          const Vector<double>*,
          const Vector<Vector<unsigned int> >*,
          const Vector<Vector<UniqueParameter> >*,
          UniqueParameter*,MonomerPropagator*,const unsigned int,
          const unsigned int,DistanceEvalDirect&,const FreeSpace&) {
  cout<<"step hierarchy"<<endl;
}

int main() {
  cout<<"Test -- initialize"<<endl;
  Propagator<DistanceEvalDirect,FreeSpace> P;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(P);
  *(P.MoveMode)=1;
  allocate(P.GSet,2);
  P.GSet[0]=seta;
  P.GSet[1]=setb;
  allocate(P.GParam,4);
  P.GSync=sync;
  P.FOutput=out;
  P.HOutput=out;
  P.FStep=step;
  P.HStep=step;
  cout<<endl;

  cout<<"Test -- build units"<<endl;
  Vector<unsigned int> ut;
  allocate(ut,3);
  assign(ut,1);
  buildUnit(P,ut);
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  Propagator<DistanceEvalDirect,FreeSpace> P2;
  allocate(P2);
  *(P2.MoveMode)=2;
  assign(P2,P);
  cout<<*(P2.MoveMode)<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(P2);
  cout<<endl;

  cout<<"Test -- check availability"<<endl;
  cout<<IsAvailable(P)<<endl;
  cout<<IsAvailable(P2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(P2,P);
  cout<<endl;

  allocate(P.GParam,NumberParameterCommon);
  P.GParam[TotalTime]=100.;
  P.GParam[OutputInterval]=10.;
  P.GParam[DeltaTime]=5.;
  for(unsigned int i=0;i<P.Unit.size;++i) P.Unit[i].MSync=msync;

  cout<<"Test -- synchronize"<<endl;
  PropertyList<double> ivMass, dMask, Vel;
  Vector<unsigned int> sz;
  allocate(sz,3);
  assign(sz,2);
  allocate(ivMass,sz);
  allocate(dMask,sz);
  allocate(Vel,sz);
  synchronize(P,ivMass.structure,dMask.structure,Vel.structure,3);
  cout<<endl;

  DistanceEvalDirect DEval;
  FreeSpace FS;

  cout<<"Test -- write"<<endl;
  Write(P,static_cast<InteractionMethod<DistanceEvalDirect,FreeSpace>*>(NULL),
        static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
        static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
        static_cast<Vector<double>*>(NULL),
        static_cast<Vector<unsigned int>*>(NULL),
        static_cast<Vector<UniqueParameter>*>(NULL),0,0,DEval,FS);
  Write(P,static_cast<InteractionMethod<DistanceEvalDirect,FreeSpace>*>(NULL),
        static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
        static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
        static_cast<Vector<double>*>(NULL),
        static_cast<Vector<Vector<unsigned int> >*>(NULL),
        static_cast<Vector<Vector<UniqueParameter> >*>(NULL),0,0,DEval,FS);
  cout<<endl;

  cout<<"Test -- step"<<endl;
  Step(P,static_cast<InteractionMethod<DistanceEvalDirect,FreeSpace>*>(NULL),
       static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
       static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
       static_cast<Vector<double>*>(NULL),
       static_cast<Vector<unsigned int>*>(NULL),
       static_cast<Vector<UniqueParameter>*>(NULL),0,0,DEval,FS);
  Step(P,static_cast<InteractionMethod<DistanceEvalDirect,FreeSpace>*>(NULL),
       static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
       static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
       static_cast<Vector<double>*>(NULL),
       static_cast<Vector<Vector<unsigned int> >*>(NULL),
       static_cast<Vector<Vector<UniqueParameter> >*>(NULL),0,0,DEval,FS);
  cout<<endl;

  cout<<"Test -- Run"<<endl;
  Run(P,
       static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
       static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
       static_cast<Vector<double>*>(NULL),
       static_cast<InteractionMethod<DistanceEvalDirect,FreeSpace>*>(NULL),
       static_cast<Vector<unsigned int>*>(NULL),
       static_cast<Vector<UniqueParameter>*>(NULL),0,0,DEval,FS);
  Run(P,
       static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
       static_cast<Vector<double>*>(NULL),static_cast<Vector<double>*>(NULL),
       static_cast<Vector<double>*>(NULL),
       static_cast<InteractionMethod<DistanceEvalDirect,FreeSpace>*>(NULL),
       static_cast<Vector<Vector<unsigned int> >*>(NULL),
       static_cast<Vector<Vector<UniqueParameter> >*>(NULL),0,0,DEval,FS);
  cout<<endl;

  return 0;
}


