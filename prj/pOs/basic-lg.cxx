
#include "operation/parameter/propagator-op.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/interaction-parameter-regular-op.h"
#include "operation/interaction/calc.h"
#include "operation/parameter/build-param-propagator-vverlet.h"
#include "operation/parameter/build-param-ext-object-lj612cut.h"
#include "operation/parameter/build-param-shifted-fene.h"
#include "operation/parameter/build-param-lj612cut.h"
#include "operation/parameter/build-param-spheric-shell-property.h"
#include "operation/propagate/run.h"
#include "data/random/regular.h"
#include "operation/random/random-generator-boxmuller-op.h"
#include "operation/random/random-generator-op.h"
#include <cstdio>
using namespace std;

template <typename T, typename ParameterType,
          template<typename,template<typename>class,typename> class IType,
          template <typename> class DBuffer, typename GeomType>
void OutFunc(Propagator<T>& P, IType<T,DBuffer,GeomType>& F,
             const ParameterType& Pm, ostream& os) {
  T E,kE;
  E=kE=0.;
  CalcInteraction(F,P.X,Pm,E);
  for(unsigned int i=0;i<P.V.nunit;++i)
    kE+=
    0.5*static_cast<UniqueParameter&>(P.sysPg[0].merPg[i][MassData]).value<T>()
       *normSQ(P.V[i]);
  os<<static_cast<UniqueParameter&>(P[NowTime]).value<T>();
  os<<"\t"<<E<<"\t"<<kE<<endl;
}


int main() {

  cout.precision(16);
  const unsigned int nunit=100;

  Propagator<double> P;
  Vector<unsigned int> enstype;
  Vector<Vector<unsigned int> > mtype;
  allocate(enstype,1);
  allocate(mtype,1);
  allocate(mtype[0],nunit);
  enstype[0]=Langevin;
  copy(mtype,ParticleType);
  allocate<Vector<InteractionParameterUnit>,ListInteraction,
           DistanceBufferSimple,FreeSpace>(P,VelocityVerlet,enstype,mtype);

  GaussianRNG grng;
  allocate(grng);
  init(grng,12721849);

  PropertyList<double> X,V,G,dMsk,RandV;
  Vector<unsigned int> sz;
  allocate(sz,nunit);
  copy(sz,3);
  allocate(X,sz);
  allocate(V,sz);
  allocate(G,sz);
  allocate(dMsk,sz);
  allocate(RandV,sz);
  copy(X,0.);
  for(unsigned int i=0;i<nunit;++i) {
    X[i][0]=i;
    X[i][1]=6.;
  }
  fillarray(grng,V);
  scale(V,0.01);
  copy(G,0.);
  copy(dMsk,1.);
  refer(P.X,X);
  refer(P.V,V);
  refer(P.G,G);
  refer(P.Msk,dMsk);

  PropertyList<unsigned int> id;
  allocate(sz,1);
  copy(sz,nunit);
  allocate(id,sz);
  for(unsigned int i=0;i<nunit;++i) id[0][i]=i;
  mapData(P,id);

  P[StartTime].d=0.;
  P[TotalTime].d=1000;
  P[OutputInterval].d=0.01;
  P.sysPg[0][TimeStep].d=0.001;
  P.sysPg[0][LV_Temperature].d=0.1;
  P.sysPg[0][LV_Viscosity].d=0.5;
  P.sysPg[0][LV_GaussianRNG].ptr=reinterpret_cast<void*>(&grng);
  for(unsigned int i=0;i<nunit;++i) {
    P.sysPg[0].merPg[i][MassData].d=1.;
    P.sysPg[0].merPg[i][PLV_HydrodynamicRadius].d=1.;
    P.sysPg[0].merPg[i][PLV_RandomVelocity].ptr=
        reinterpret_cast<void*>(RandV.structure+i);
  }
  BuildParameterPropagatorVVerlet(P);

  ListInteraction<double,DistanceBufferSimple,FreeSpace> F;
  allocate(sz,(nunit*(nunit+1))/2);
  for(unsigned int i=0;i<nunit;++i) sz[i]=SphericShellLJ612Cut;
  for(unsigned int i=0,n=nunit;i<nunit-1;++i) sz[n++]=ShiftedFENE;
  for(unsigned int i=0,n=nunit+nunit-1;i<nunit;++i)
  for(unsigned int j=i+2;j<nunit;++j)   sz[n++]=LJ612Cut;
  allocate(F,sz,3,nunit);
  
  Vector<InteractionParameterUnit> Prm;
  allocate(Prm,(nunit*(nunit+1))/2);
  for(unsigned int i=0;i<nunit;++i) allocate(Prm[i],SphericShellLJ612Cut);
  for(unsigned int i=0,n=nunit;i<nunit-1;++i) allocate(Prm[n++],ShiftedFENE);
  for(unsigned int i=0,n=nunit+nunit-1;i<nunit;++i)
  for(unsigned int j=i+2;j<nunit;++j) allocate(Prm[n++],LJ612Cut);
  
  Vector<double> wv;
  Vector<UniqueParameter> pprop;
  allocate(wv,3);
  allocate(pprop,SphericShellPropertyNumberParameter);
  copy(wv,0.);
  pprop[SphericShellRadius].d=5.;
  pprop[SphericShellDirection].d=1;
  BuildParameterSphericShellProperty<double>(pprop);
  for(unsigned int i=0;i<nunit;++i) {
    Prm[i].prm[ExtObjectLocationPointer].ptr=reinterpret_cast<void*>(&wv);
    Prm[i].prm[ExtObjectPropertyPointer].ptr=reinterpret_cast<void*>(&pprop);
    Prm[i].prm[ExtObjLJ612CutEqRadius].d=1.;
    Prm[i].prm[ExtObjLJ612CutEqEnergyDepth].d=4.;
    Prm[i].prm[ExtObjLJ612CutCutR].d=5.;
    BuildParameterExtObjLJ612Cut<double>(Prm[i].prm);
  }
  for(unsigned int  i=0,n=nunit;i<nunit-1;++i,++n) {
    Prm[n].prm[SfFENEStrength].d=2*P.sysPg[0][LV_Temperature].d*100;
    Prm[n].prm[SfFENEEqLength].d=1.;
    Prm[n].prm[SfFENEDeltaRadiusMax].d=0.3;
    BuildParameterShiftedFENE<double>(Prm[n].prm);
  }
  for(unsigned int i=0,n=nunit+nunit-1;i<nunit;++i)
  for(unsigned int j=i+2;j<nunit;++j,++n) {
    Prm[n].prm[LJ612CutEqRadius].d=1.;
    Prm[n].prm[LJ612CutEqEnergyDepth].d=0.1;
    Prm[n].prm[LJ612CutCutR].d=5.0;
    BuildParameterLJ612Cut<double>(Prm[n].prm);
  }
  for(unsigned int i=0;i<nunit;++i) Prm[i].idx[0]=i;
  for(unsigned int i=0,n=nunit;i<nunit-1;++i,++n) {
    Prm[n].idx[0]=i;
    Prm[n].idx[1]=i+1;
  }
  for(unsigned int i=0,n=nunit+nunit-1;i<nunit;++i)
  for(unsigned int j=i+2;j<nunit;++j,++n) {
    Prm[n].idx[0]=i;
    Prm[n].idx[1]=j;
  }

  copy(P.G,0.);
  CalcInteraction(F,P.X,Prm,P.G);

  assignOutput(P,OutFunc<double,Vector<InteractionParameterUnit>,
                         ListInteraction,DistanceBufferSimple,FreeSpace>);
  Run(P,F,Prm);

  return 0;
}

