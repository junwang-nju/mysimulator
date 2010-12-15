
#include "operation/parameter/build-param-propagator-vverlet.h"
#include "operation/parameter/propagator-op.h"
#include "operation/interaction/calc.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/parameter/build-param-lj612.h"
#include "operation/propagate/run.h"
#include "data/random/regular.h"
#include "operation/random/random-generator-boxmuller-op.h"
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
      0.5*
      static_cast<UniqueParameter&>(P.sysPg[0].merPg[i][MassData]).value<T>()*
      normSQ(P.V[i]);
  os<<static_cast<UniqueParameter&>(P[NowTime]).value<T>();
  os<<"\t"<<E<<"\t"<<kE<<endl;
}

int main() {
  Propagator<double> P;
  Vector<unsigned int> enstype;
  Vector<Vector<unsigned int> > mtype;
  allocate(enstype,1);
  allocate(mtype,1);
  allocate(mtype[0],4);
  enstype[0]=Langevin;
  copy(mtype,ParticleType);
  allocate<Vector<InteractionParameterUnit>,ListInteraction,
           DistanceBufferSimple,FreeSpace>(P,VelocityVerlet,enstype,mtype);

  PropertyList<double> X,V,G,dMsk,RandV;
  Vector<unsigned int> sz;
  allocate(sz,4);
  copy(sz,2);
  allocate(X,sz);
  allocate(V,sz);
  allocate(G,sz);
  allocate(dMsk,sz);
  allocate(RandV,sz);
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
  for(unsigned int i=0;i<4;++i) id[0][i]=i;
  mapData(P,id);

  P[StartTime].d=100.;
  P[TotalTime].d=10.;
  P[OutputInterval].d=0.1;

  GaussianRNG grng;
  allocate(grng);
  init(grng,1237913);
  P.sysPg[0][TimeStep].d=0.001;
  P.sysPg[0][LV_Temperature].d=0.5;
  P.sysPg[0][LV_Viscosity].d=0.5;
  P.sysPg[0][LV_GaussianRNG].ptr=reinterpret_cast<void*>(&grng);
  for(unsigned int i=0;i<4;++i) {
    P.sysPg[0].merPg[i][MassData].d=2.;
    P.sysPg[0].merPg[i][PLV_HydrodynamicRadius].d=1.;
    P.sysPg[0].merPg[i][PLV_RandomVelocity].ptr=
        reinterpret_cast<void*>(RandV.structure+i);
  }

  BuildParameterPropagatorVVerlet(P);

  ListInteraction<double,DistanceBufferSimple,FreeSpace> F;
  allocate(sz,6);
  for(unsigned int i=0;i<3;++i) sz[i]=Harmonic;
  for(unsigned int i=3;i<6;++i) sz[i]=LJ612;
  allocate(F,sz,2,4);
  
  Vector<InteractionParameterUnit> RP(6);
  for(unsigned int i=0;i<3;++i) allocate(RP[i],Harmonic);
  for(unsigned int i=3;i<6;++i) allocate(RP[i],LJ612);
  RP[0].prm[HarmonicEqLength].d=1.;
  RP[0].prm[HarmonicEqStrength].d=100.;
  RP[1].prm[HarmonicEqLength].d=1.;
  RP[1].prm[HarmonicEqStrength].d=100.;
  RP[2].prm[HarmonicEqLength].d=1.;
  RP[2].prm[HarmonicEqStrength].d=100.;
  for(unsigned int i=0;i<3;++i) BuildParameterHarmonic<double>(RP[i].prm);
  RP[3].prm[LJ612EqRadius].d=1.;
  RP[3].prm[LJ612EqEnergyDepth].d=1.;
  RP[4].prm[LJ612EqRadius].d=1.;
  RP[4].prm[LJ612EqEnergyDepth].d=1.;
  RP[5].prm[LJ612EqRadius].d=1.;
  RP[5].prm[LJ612EqEnergyDepth].d=1.;
  for(unsigned int i=3;i<6;++i) BuildParameterLJ612<double>(RP[i].prm);
  RP[0].idx[0]=0;       RP[0].idx[1]=1;
  RP[1].idx[0]=1;       RP[1].idx[1]=2;
  RP[2].idx[0]=2;       RP[2].idx[1]=3;
  RP[3].idx[0]=0;       RP[3].idx[1]=2;
  RP[4].idx[0]=0;       RP[4].idx[1]=3;
  RP[5].idx[0]=1;       RP[5].idx[1]=3;

  copy(P.G,0.);
  CalcInteraction(F,P.X,RP,P.G);
  cout<<P.G<<endl;

  typedef void (*MoveFunc)(
            Propagator<double>&,
            ListInteraction<double,DistanceBufferSimple,FreeSpace>&,
            const Vector<InteractionParameterUnit>&);
  cout<<"========== X:"<<endl;
  cout<<P.X<<endl;
  cout<<"========== V:"<<endl;
  cout<<P.V<<endl;
  cout<<"========== G:"<<endl;
  cout<<P.G<<endl;
  reinterpret_cast<MoveFunc>(P[PgStep].ptr)(P,F,RP);
  cout<<"========== X:"<<endl;
  cout<<P.X<<endl;
  cout<<"========== V:"<<endl;
  cout<<P.V<<endl;
  cout<<"========== G:"<<endl;
  cout<<P.G<<endl;

  P[TotalTime].d=400;
  P[OutputInterval].d=0.001;
  BuildParameterPropagatorVVerlet(P);
  assignOutput(P,OutFunc<double,Vector<InteractionParameterUnit>,
                         ListInteraction,DistanceBufferSimple,FreeSpace>);

  cout<<endl;
  Run(P,F,RP);

  return 1;
}
