
#include "operation/parameter/propagator-op.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/interaction-parameter-regular-op.h"
#include "operation/interaction/calc.h"
#include "operation/parameter/build-param-propagator-vverlet.h"
#include "data/random/regular.h"
#include "operation/random/random-generator-boxmuller-op.h"
#include "operation/random/random-generator-op.h"
using namespace std;

int main() {

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
  P[TotalTime].d=100000.;
  P[OutputInterval].d=0.1;
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
  allocate(sz,);

  return 0;
}

