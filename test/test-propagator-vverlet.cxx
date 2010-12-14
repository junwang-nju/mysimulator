
#include "operation/parameter/build-param-propagator-vverlet.h"
#include "operation/parameter/propagator-op.h"
#include "operation/interaction/calc.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
using namespace std;

int main() {
  Propagator<double> P;
  Vector<unsigned int> enstype;
  Vector<Vector<unsigned int> > mtype;
  allocate(enstype,1);
  allocate(mtype,1);
  allocate(mtype[0],4);
  enstype[0]=ConstantE;
  copy(mtype,ParticleType);
  allocate<Vector<InteractionParameterUnit>,ListInteraction,
           DistanceBufferSimple,FreeSpace>(P,VelocityVerlet,enstype,mtype);

  PropertyList<double> X,V,G,dMsk;
  Vector<unsigned int> sz;
  allocate(sz,4);
  copy(sz,2);
  allocate(X,sz);
  allocate(V,sz);
  allocate(G,sz);
  allocate(dMsk,sz);
  X[0][0]=0;       X[0][1]=0;
  X[1][0]=0;       X[1][1]=1.2;
  X[2][0]=1.3;     X[2][1]=1.5;
  X[3][0]=0.8;     X[3][1]=2.2;
  copy(V,0.);
  copy(dMsk,1.);
  refer(P.X,X);
  refer(P.V,V);
  refer(P.G,G);
  refer(P.Msk,dMsk);
  PropertyList<unsigned int> id;
  allocate(sz,1);
  copy(sz,4);
  allocate(id,sz);
  mapData(P,id);

  P[StartTime].d=100.;
  P[TotalTime].d=10.;
  P[OutputInterval].d=0.1;

  P.sysPg[0][TimeStep].d=0.001;
  for(unsigned int i=0;i<4;++i) P.sysPg[0].merPg[i][MassData].d=2.;

  BuildParameterPropagatorVVerlet(P);
  return 1;
}

