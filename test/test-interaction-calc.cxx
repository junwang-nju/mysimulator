
#include "operation/interaction/calc.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/parameter/build-param-lj612.h"
#include "operation/basic/map-op.h"
#include "operation/basic/build-hash.h"
#include "data/basic/console-output.h"
#include "operation/basic/property-list-io.h"
using namespace std;

int main() {
  COut<<"Test -- initialize interaction"<<Endl;
  SimpleInteraction<double,DistanceBufferSimple,FreeSpace> F;
  InteractionParameterUnit P;
  COut<<Endl;
  
  COut<<"Test -- allocate Interaction"<<Endl;
  allocate(F,Harmonic,3,2);
  allocate(P,Harmonic);
  COut<<Endl;

  COut<<"Test -- copy Interaction"<<Endl;
  SimpleInteraction<double,DistanceBufferSimple,FreeSpace> F2;
  InteractionParameterUnit P2;
  allocate(F2,Harmonic,3,2);
  allocate(P2,Harmonic);
  copy(F2,F);
  copy(P2,P);
  COut<<Endl;
  
  COut<<"Test -- refer Interaction"<<Endl;
  SimpleInteraction<double,DistanceBufferSimple,FreeSpace> F3;
  InteractionParameterUnit P3;
  refer(F3,F);
  refer(P3,P);
  COut<<Endl;

  COut<<"Test -- release Interaction"<<Endl;
  release(F2);
  release(P2);
  COut<<Endl;
  
  COut<<"Test - Interaction Calc"<<Endl;
  P.prm[HarmonicEqLength].d=1.;
  P.prm[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(P.prm);
  Vector<unsigned int> sz(2);
  copy(sz,3);
  PropertyList<double> v,g;
  allocate(v,sz);
  allocate(g,sz);
  copy(v,0.);
  v[1][0]=1.3;
  P.idx[0]=0; P.idx[1]=1;
  double E;
  E=0;
  CalcInteraction(F,v.structure,P,E);
  COut<<E<<Endl;
  copy(g,0.);
  CalcInteraction(F,v.structure,P,g.structure);
  COut<<g<<Endl;
  E=0.;
  copy(g,0.);
  CalcInteraction(F,v.structure,P,E,g.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- simple interaction & vector parameter"<<Endl;
  allocate(sz,4);
  copy(sz,3);
  allocate(v,sz);
  allocate(g,sz);
  copy(v,0.);
  v[1][1]=1.2;
  v[2][0]=1.3;    v[2][1]=1.5;
  v[3][0]=0.8;    v[3][1]=2.2;
  Vector<InteractionParameterUnit> PV;
  allocate(PV,6);
  for(unsigned int i=0;i<6;++i)   allocate(PV[i],Harmonic);
  PV[0].idx[0]=0;     PV[0].idx[1]=1;
  PV[1].idx[0]=0;     PV[1].idx[1]=2;
  PV[2].idx[0]=0;     PV[2].idx[1]=3;
  PV[3].idx[0]=1;     PV[3].idx[1]=2;
  PV[4].idx[0]=1;     PV[4].idx[1]=3;
  PV[5].idx[0]=2;     PV[5].idx[1]=3;

  Map<Vector<unsigned int>,Vector<UniqueParameter> > PL;
  allocate(PL);
  Vector<unsigned int> key;
  Vector<UniqueParameter> value;
  allocate(key,3);
  allocate(value,HarmonicNumberParameter);

  for(unsigned int i=0,n=0;i<3;++i)
  for(unsigned int j=0;j<3;++j,++n) {
    key[0]=Harmonic;
    key[1]=i;
    key[2]=j;
  }
  key[0]=Harmonic;

  key[1]=0;
  key[2]=0;
  value[HarmonicEqLength].d=1.;
  value[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);

  key[1]=0;
  key[2]=1;
  value[HarmonicEqLength].d=2.;
  value[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);
  key[1]=1;
  key[2]=0;
  add(PL,key,value,Allocated,Allocated);

  key[1]=0;
  key[2]=2;
  value[HarmonicEqLength].d=0.5;
  value[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);
  key[1]=2;
  key[2]=0;
  add(PL,key,value,Allocated,Allocated);

  key[1]=1;
  key[2]=1;
  value[HarmonicEqLength].d=1.;
  value[HarmonicEqStrength].d=200.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);

  key[1]=1;
  key[2]=2;
  value[HarmonicEqLength].d=1.;
  value[HarmonicEqStrength].d=30.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);
  key[1]=2;
  key[2]=1;
  add(PL,key,value,Allocated,Allocated);

  key[1]=2;
  key[2]=2;
  value[HarmonicEqLength].d=1.5;
  value[HarmonicEqStrength].d=2000.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);

  Vector<unsigned int> Kind(4);
  copy(Kind,0);
  Kind[1]=1;
  Kind[3]=2;
  allocate(sz,3);
  for(unsigned int i=0;i<PV.size;++i) {
    sz[0]=Harmonic;
    sz[1]=Kind[PV[i].idx[0]];
    sz[2]=Kind[PV[i].idx[1]];
    refer(PV[i].prm,*get(PL,sz));
  }
  E=0.;
  CalcInteraction(F,v.structure,PV,E);
  COut<<E<<Endl;
  copy(g,0);
  CalcInteraction(F,v.structure,PV,g.structure);
  COut<<g<<Endl;
  copy(g,0);
  E=0.;
  CalcInteraction(F,v.structure,PV,E,g.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- initialize List Interaction"<<Endl;
  ListInteraction<double,DistanceBufferSimple,FreeSpace> LF;
  COut<<Endl;

  COut<<"Test -- allocate List Interaction"<<Endl;
  allocate(sz,6);
  for(unsigned int i=0;i<6;++i) sz[i]=Harmonic;
  allocate(LF,sz,3,4);
  COut<<Endl;

  COut<<"Test -- copy List Interaction"<<Endl;
  ListInteraction<double,DistanceBufferSimple,FreeSpace> LF2;
  allocate(sz,6);
  for(unsigned int i=0;i<6;++i) sz[i]=Harmonic;
  allocate(LF2,sz,3,4);
  copy(LF2,LF);
  COut<<Endl;

  COut<<"Test -- refer List Interaction"<<Endl;
  ListInteraction<double,DistanceBufferSimple,FreeSpace> LF3;
  refer(LF3,LF);
  COut<<Endl;

  COut<<"Test -- release List Interaction"<<Endl;
  release(LF2);
  COut<<Endl;
  
  COut<<"Test -- List Interaction Calculation"<<Endl;
  E=0.;
  CalcInteraction(LF,v.structure,PV,E);
  COut<<E<<Endl;
  copy(g,0);
  CalcInteraction(LF,v.structure,PV,g.structure);
  COut<<g<<Endl;
  copy(g,0);
  E=0.;
  CalcInteraction(LF,v.structure,PV,E,g.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- list interaction & property parameter"<<Endl;
  allocate(sz,2);
  sz[0]=Harmonic;
  sz[1]=LJ612;
  allocate(LF,sz,3,4);
  PropertyList<InteractionParameterUnit> PP;
  allocate(sz,2);
  copy(sz,3);
  allocate(PP,sz);
  for(unsigned int j=0;j<3;++j)   allocate(PP[0][j],Harmonic);
  for(unsigned int j=0;j<3;++j)   allocate(PP[1][j],LJ612);
  PP[0][0].idx[0]=0;     PP[0][0].idx[1]=1;
  PP[0][1].idx[0]=0;     PP[0][1].idx[1]=2;
  PP[0][2].idx[0]=0;     PP[0][2].idx[1]=3;
  PP[1][0].idx[0]=1;     PP[1][0].idx[1]=2;
  PP[1][1].idx[0]=1;     PP[1][1].idx[1]=3;
  PP[1][2].idx[0]=2;     PP[1][2].idx[1]=3;

  allocate(PL);
  allocate(key,3);
  allocate(value,HarmonicNumberParameter);
  key[0]=Harmonic;

  key[1]=0;
  key[2]=0;
  value[HarmonicEqLength].d=1.;
  value[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);

  key[1]=0;
  key[2]=1;
  value[HarmonicEqLength].d=2.;
  value[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);
  key[1]=1;
  key[2]=0;
  add(PL,key,value,Allocated,Allocated);

  key[1]=0;
  key[2]=2;
  value[HarmonicEqLength].d=0.5;
  value[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);
  key[1]=2;
  key[2]=0;
  add(PL,key,value,Allocated,Allocated);

  key[1]=1;
  key[2]=1;
  value[HarmonicEqLength].d=1.;
  value[HarmonicEqStrength].d=200.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);

  key[1]=1;
  key[2]=2;
  value[HarmonicEqLength].d=1.;
  value[HarmonicEqStrength].d=30.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);
  key[1]=2;
  key[2]=1;
  add(PL,key,value,Allocated,Allocated);

  key[1]=2;
  key[2]=2;
  value[HarmonicEqLength].d=1.5;
  value[HarmonicEqStrength].d=2000.;
  BuildParameterHarmonic<double>(value);
  add(PL,key,value,Allocated,Allocated);

  allocate(value,LJ612NumberParameter);
  key[0]=LJ612;

  key[1]=0;
  key[2]=0;
  value[LJ612EqRadius].d=1.;
  value[LJ612EqEnergyDepth].d=1.;
  BuildParameterLJ612<double>(value);
  add(PL,key,value,Allocated,Allocated);

  key[1]=0;
  key[2]=1;
  value[LJ612EqRadius].d=0.8;
  value[LJ612EqEnergyDepth].d=2.;
  BuildParameterLJ612<double>(value);
  add(PL,key,value,Allocated,Allocated);
  key[1]=1;
  key[2]=0;
  add(PL,key,value,Allocated,Allocated);

  key[1]=0;
  key[2]=2;
  value[LJ612EqRadius].d=0.5;
  value[LJ612EqEnergyDepth].d=1.;
  BuildParameterLJ612<double>(value);
  add(PL,key,value,Allocated,Allocated);
  key[1]=2;
  key[2]=0;
  add(PL,key,value,Allocated,Allocated);

  key[1]=1;
  key[2]=1;
  value[LJ612EqRadius].d=1.2;
  value[LJ612EqEnergyDepth].d=2.;
  BuildParameterLJ612<double>(value);
  add(PL,key,value,Allocated,Allocated);

  key[1]=1;
  key[2]=2;
  value[LJ612EqRadius].d=1.1;
  value[LJ612EqEnergyDepth].d=3.;
  BuildParameterLJ612<double>(value);
  add(PL,key,value,Allocated,Allocated);
  key[1]=2;
  key[2]=1;
  add(PL,key,value,Allocated,Allocated);

  key[1]=2;
  key[2]=2;
  value[LJ612EqRadius].d=1.5;
  value[LJ612EqEnergyDepth].d=2.;
  BuildParameterLJ612<double>(value);
  add(PL,key,value,Allocated,Allocated);

  allocate(sz,3);
  for(unsigned int i=0;i<3;++i) {
    sz[0]=Harmonic;
    sz[1]=Kind[PP[0][i].idx[0]];
    sz[2]=Kind[PP[0][i].idx[1]];
    refer(PP[0][i].prm,*get(PL,sz));
  }
  for(unsigned int i=0;i<3;++i) {
    sz[0]=LJ612;
    sz[1]=Kind[PP[1][i].idx[0]];
    sz[2]=Kind[PP[1][i].idx[1]];
    refer(PP[1][i].prm,*get(PL,sz));
  }
  E=0.;
  CalcInteraction(LF,v.structure,PP,E);
  COut<<E<<Endl;
  copy(g,0.);
  CalcInteraction(LF,v.structure,PP,g.structure);
  COut<<g<<Endl;
  E=0.;
  copy(g,0.);
  CalcInteraction(LF,v.structure,PP,E,g.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- list interaction & vector-vector parameter"<<Endl;
  Vector<Vector<InteractionParameterUnit> > PVV;
  allocate(PVV,2);
  allocate(PVV[0],3);
  allocate(PVV[1],3);
  for(unsigned int i=0;i<3;++i) allocate(PVV[0][i],Harmonic);
  for(unsigned int i=0;i<3;++i) allocate(PVV[1][i],Harmonic);
  PVV[0][0].idx[0]=0;     PVV[0][0].idx[1]=1;
  PVV[0][1].idx[0]=0;     PVV[0][1].idx[1]=2;
  PVV[0][2].idx[0]=0;     PVV[0][2].idx[1]=3;
  PVV[1][0].idx[0]=1;     PVV[1][0].idx[1]=2;
  PVV[1][1].idx[0]=1;     PVV[1][1].idx[1]=3;
  PVV[1][2].idx[0]=2;     PVV[1][2].idx[1]=3;
  allocate(sz,3);
  for(unsigned int i=0;i<3;++i) {
    sz[0]=Harmonic;
    sz[1]=Kind[PVV[0][i].idx[0]];
    sz[2]=Kind[PVV[0][i].idx[1]];
    refer(PVV[0][i].prm,*get(PL,sz));
  }
  for(unsigned int i=0;i<3;++i) {
    sz[0]=LJ612;
    sz[1]=Kind[PVV[1][i].idx[0]];
    sz[2]=Kind[PVV[1][i].idx[1]];
    refer(PVV[1][i].prm,*get(PL,sz));
  }
  E=0.;
  CalcInteraction(LF,v.structure,PVV,E);
  COut<<E<<Endl;
  copy(g,0.);
  CalcInteraction(LF,v.structure,PVV,g.structure);
  COut<<g<<Endl;
  E=0.;
  copy(g,0.);
  CalcInteraction(LF,v.structure,PVV,E,g.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  return 0;
}

