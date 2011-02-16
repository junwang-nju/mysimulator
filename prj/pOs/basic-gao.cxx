
#include "operation/parameter/propagator-op.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/interaction-parameter-regular-op.h"
#include "operation/parameter/interaction-parameter-meta-op.h"
#include "operation/interaction/meta-calc.h"
#include "operation/parameter/build-param-propagator-vverlet.h"
#include "operation/parameter/build-param-ext-object-lj612cut.h"
#include "operation/parameter/build-param-shifted-fene.h"
#include "operation/parameter/build-param-lj612cut.h"
#include "operation/parameter/build-param-ext-object-harmonic.h"
#include "operation/parameter/build-param-spheric-shell-property.h"
#include "operation/parameter/build-param-gao-enhanced-sampling.h"
#include "operation/propagate/run.h"
#include "data/random/regular.h"
#include "operation/random/random-generator-boxmuller-op.h"
#include "operation/random/random-generator-op.h"
#include "data/basic/console-output.h"
#include "data/basic/simple-data-output.h"
using namespace std;

template <typename T, typename ParameterType,
          template<typename,template<typename>class,typename> class IType,
          template <typename> class DBuffer, typename GeomType>
void OutFunc(Propagator<T>& P, IType<T,DBuffer,GeomType>& F,
             ParameterType& Pm, OutputBase& os) {
  //T E,kE;
  T U;
  //E=kE=0.;
  U=0.;
  //CalcInteraction(F,P.X,Pm,E);
  CalcInteraction(F,P.X,Pm.inprm,U);
  /*
  for(unsigned int i=0;i<P.V.nunit;++i)
    kE+=
    0.5*static_cast<UniqueParameter&>(P.sysPg[0].merPg[i][MassData]).value<T>()
       *normSQ(P.V[i]);
  os<<static_cast<UniqueParameter&>(P[NowTime]).value<T>();
  os<<"\t"<<E<<"\t"<<kE<<"\t"<<U<<Endl;
  */
  os<<U<<Endl;
}


int main() {

  COut.precision(16);
  const unsigned int nunit=100;

  typedef InteractionMetaParameter<Vector<InteractionParameterUnit>,
                                   ListInteraction<double,DistanceBufferSimple,
                                                   FreeSpace>,
                                   double>
  ParamType;

  Propagator<double> P;
  Vector<unsigned int> enstype;
  Vector<Vector<unsigned int> > mtype;
  allocate(enstype,1);
  allocate(mtype,1);
  allocate(mtype[0],nunit);
  enstype[0]=Langevin;
  copy(mtype,ParticleType);
  allocate<ParamType,ListInteraction,
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
  P[TotalTime].d=100;
  P[OutputInterval].d=0.01;
  P.sysPg[0][TimeStep].d=0.001;
  P.sysPg[0][LV_Temperature].d=1;
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
  allocate(sz,(nunit*(nunit+1))/2+nunit);
  for(unsigned int i=0;i<nunit;++i) sz[i]=SphericShellLJ612Cut;
  for(unsigned int i=0,n=nunit;i<nunit-1;++i) sz[n++]=ShiftedFENE;
  for(unsigned int i=0,n=nunit+nunit-1;i<nunit;++i)
  for(unsigned int j=i+2;j<nunit;++j)   sz[n++]=LJ612Cut;
  for(unsigned int i=0,n=(nunit*(nunit+1))/2;i<nunit;++i)
    sz[n++]=AnchorPointHarmonic;
  allocate(F,sz,3,nunit);
  
  Vector<InteractionParameterUnit> Prm;
  allocate(Prm,(nunit*(nunit+1))/2+nunit);
  for(unsigned int i=0;i<nunit;++i) allocate(Prm[i],SphericShellLJ612Cut);
  for(unsigned int i=0,n=nunit;i<nunit-1;++i) allocate(Prm[n++],ShiftedFENE);
  for(unsigned int i=0,n=nunit+nunit-1;i<nunit;++i)
  for(unsigned int j=i+2;j<nunit;++j) allocate(Prm[n++],LJ612Cut);
  for(unsigned int i=0,n=(nunit*(nunit+1))/2;i<nunit;++i)
    allocate(Prm[n++],AnchorPointHarmonic);
  
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
    Prm[n].prm[SfFENEStrength].d=2*8*100;//2*P.sysPg[0][LV_Temperature].d*100;
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
  for(unsigned int i=0,n=(nunit*(nunit+1))/2;i<nunit;++i,++n) {
    Prm[n].prm[ExtObjectLocationPointer].ptr=reinterpret_cast<void*>(&wv);
    Prm[n].prm[ExtObjHarmonicEqLength].d=6.;
    Prm[n].prm[ExtObjHarmonicEqStrength].d=0.1;
    BuildParameterExtObjHarmonic<double>(Prm[n].prm);
  }

  ParamType MP;
  allocate(MP,GaoEnhancedSampling);
  refer(MP.inprm,Prm);
  Vector<double> ds,ts,lnds,bt,lnbd;
  const unsigned int nT=6;
  allocate(ds,nT);
  allocate(ts,nT);
  allocate(lnds,nT);
  allocate(bt,nT);
  allocate(lnbd,nT);
  copy(ds,1.);
  ts[5]=1.;
  ts[4]=1.2;
  ts[3]=1.6;
  ts[2]=2.;
  ts[1]=3.;
  ts[0]=5.;
  ds[0]=exp(-204.);
  ds[1]=exp(-165.);
  ds[2]=exp(-108.);
  ds[3]=exp(-95.);
  ds[4]=exp(-38.);
  ds[5]=1;
  MP.prm[DensitySet].ptr=reinterpret_cast<void*>(&ds);
  MP.prm[TemperatureSet].ptr=reinterpret_cast<void*>(&ts);
  MP.prm[LnDensitySet].ptr=reinterpret_cast<void*>(&lnds);
  MP.prm[BetaSet].ptr=reinterpret_cast<void*>(&bt);
  MP.prm[LnBetaDensitySet].ptr=reinterpret_cast<void*>(&lnbd);
  MP.prm[RunTemperature].d=P.sysPg[0][LV_Temperature].d;
  MP.prm[GaoNumberAllUnits].u=nunit;
  BuildParameterGaoEnhancedSampling<double>(MP.prm);

  Vector<double> pb;
  allocate(pb,ts.size);

  copy(P.G,0.);
  CalcInteraction(F,P.X,MP,P.G);

  assignOutput(P,OutFunc<double,ParamType,
                         ListInteraction,DistanceBufferSimple,FreeSpace>);
  SimpleDataOutput<double> SO;
  allocate(SO,P[NumberOutput].u+1);
  Run(P,F,MP,SO);

  Vector<double> vU;
  refer(vU,SO.buffer);

  for(unsigned int i=0;i<vU.size;++i)
    COut<<i<<"\t"<<vU[i]<<Endl;
  copy(pb,0.);
  unsigned int bU=static_cast<unsigned int>(0.1*vU.size);
  for(unsigned int k=0;k<pb.size;++k) {
    pb[k]=lnds[k]-bt[k]*vU[bU];
    for(unsigned int i=bU+1;i<vU.size;++i)
      pb[k]+=log1p(exp(lnds[k]-bt[k]*vU[i]-pb[k]));
    COut<<k<<"\t"<<ts[k]<<"\t"<<pb[k]<<Endl;
  }

  return 0;
}

