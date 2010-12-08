
#include "operation/interaction/calc.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/parameter/build-param-lj612.h"
#include "data/derived/parameter-list.h"
using namespace std;

int main() {
  cout<<"Test -- initialize interaction"<<endl;
  SimpleInteraction<double,DistanceBufferSimple,FreeSpace> F;
  InteractionParameterUnit P;
  cout<<endl;
  
  cout<<"Test -- allocate Interaction"<<endl;
  allocate(F,Harmonic,3,2);
  allocateIndex(P,Harmonic);
  allocateParameter(P,Harmonic);
  cout<<endl;

  cout<<"Test -- copy Interaction"<<endl;
  SimpleInteraction<double,DistanceBufferSimple,FreeSpace> F2;
  InteractionParameterUnit P2;
  allocate(F2,Harmonic,3,2);
  allocateIndex(P2,Harmonic);
  allocateParameter(P2,Harmonic);
  copy(F2,F);
  copy(P2,P);
  cout<<endl;
  
  cout<<"Test -- refer Interaction"<<endl;
  SimpleInteraction<double,DistanceBufferSimple,FreeSpace> F3;
  InteractionParameterUnit P3;
  refer(F3,F);
  refer(P3,P);
  cout<<endl;

  cout<<"Test -- release Interaction"<<endl;
  release(F2);
  release(P2);
  cout<<endl;
  
  cout<<"Test - Interaction Calc"<<endl;
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
  cout<<E<<endl;
  copy(g,0.);
  CalcInteraction(F,v.structure,P,g.structure);
  cout<<g<<endl;
  E=0.;
  copy(g,0.);
  CalcInteraction(F,v.structure,P,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- simple interaction & vector parameter"<<endl;
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
  ParameterList PL;
  allocate(PL,3,HarmonicNumberParameter,3*3);
  for(unsigned int i=0,n=0;i<3;++i)
  for(unsigned int j=0;j<3;++j,++n) {
    PL.key[n][0]=Harmonic;
    PL.key[n][1]=i;
    PL.key[n][2]=j;
    PL.key[n].update();
  }
  PL.value[0][HarmonicEqLength].d=1.;
  PL.value[0][HarmonicEqStrength].d=100.;
  PL.value[1][HarmonicEqLength].d=2.;
  PL.value[1][HarmonicEqStrength].d=100.;
  PL.value[2][HarmonicEqLength].d=0.5;
  PL.value[2][HarmonicEqStrength].d=100.;
  copy(PL.value[3],PL.value[1]);
  PL.value[4][HarmonicEqLength].d=1.;
  PL.value[4][HarmonicEqStrength].d=200.;
  PL.value[5][HarmonicEqLength].d=1.;
  PL.value[5][HarmonicEqStrength].d=30.;
  copy(PL.value[6],PL.value[2]);
  copy(PL.value[7],PL.value[5]);
  PL.value[8][HarmonicEqLength].d=1.5;
  PL.value[8][HarmonicEqStrength].d=2000.;
  for(unsigned int i=0;i<9;++i) BuildParameterHarmonic<double>(PL.value[i]);
  PL.update();
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
  cout<<E<<endl;
  copy(g,0);
  CalcInteraction(F,v.structure,PV,g.structure);
  cout<<g<<endl;
  copy(g,0);
  E=0.;
  CalcInteraction(F,v.structure,PV,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- initialize List Interaction"<<endl;
  ListInteraction<double,DistanceBufferSimple,FreeSpace> LF;
  cout<<endl;

  cout<<"Test -- allocate List Interaction"<<endl;
  allocate(sz,6);
  for(unsigned int i=0;i<6;++i) sz[i]=Harmonic;
  allocate(LF,sz,3,4);
  cout<<endl;

  cout<<"Test -- copy List Interaction"<<endl;
  ListInteraction<double,DistanceBufferSimple,FreeSpace> LF2;
  allocate(sz,6);
  for(unsigned int i=0;i<6;++i) sz[i]=Harmonic;
  allocate(LF2,sz,3,4);
  copy(LF2,LF);
  cout<<endl;

  cout<<"Test -- refer List Interaction"<<endl;
  ListInteraction<double,DistanceBufferSimple,FreeSpace> LF3;
  refer(LF3,LF);
  cout<<endl;

  cout<<"Test -- release List Interaction"<<endl;
  release(LF2);
  cout<<endl;
  
  cout<<"Test -- List Interaction Calculation"<<endl;
  E=0.;
  CalcInteraction(LF,v.structure,PV,E);
  cout<<E<<endl;
  copy(g,0);
  CalcInteraction(LF,v.structure,PV,g.structure);
  cout<<g<<endl;
  copy(g,0);
  E=0.;
  CalcInteraction(LF,v.structure,PV,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- list interaction & property parameter"<<endl;
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
  release(PL);
  allocate(sz,18);
  for(unsigned int i=0;i<9;++i)   sz[i]=HarmonicNumberParameter;
  for(unsigned int i=9;i<18;++i)  sz[i]=LJ612NumberParameter;
  allocate(PL,3,sz);
  for(unsigned int i=0,n=0;i<3;++i)
  for(unsigned int j=0;j<3;++j,++n) {
    PL.key[n][0]=Harmonic;
    PL.key[n][1]=i;
    PL.key[n][2]=j;
    PL.key[n].update();
  }
  PL.value[0][HarmonicEqLength].d=1.;
  PL.value[0][HarmonicEqStrength].d=100.;
  PL.value[1][HarmonicEqLength].d=2.;
  PL.value[1][HarmonicEqStrength].d=100.;
  PL.value[2][HarmonicEqLength].d=0.5;
  PL.value[2][HarmonicEqStrength].d=100.;
  copy(PL.value[3],PL.value[1]);
  PL.value[4][HarmonicEqLength].d=1.;
  PL.value[4][HarmonicEqStrength].d=200.;
  PL.value[5][HarmonicEqLength].d=1.;
  PL.value[5][HarmonicEqStrength].d=30.;
  copy(PL.value[6],PL.value[2]);
  copy(PL.value[7],PL.value[5]);
  PL.value[8][HarmonicEqLength].d=1.5;
  PL.value[8][HarmonicEqStrength].d=2000.;
  for(unsigned int i=0;i<9;++i) BuildParameterHarmonic<double>(PL.value[i]);
  for(unsigned int i=0,n=9;i<3;++i)
  for(unsigned int j=0;j<3;++j,++n) {
    PL.key[n][0]=LJ612;
    PL.key[n][1]=i;
    PL.key[n][2]=j;
    PL.key[n].update();
  }
  PL.value[9][LJ612EqRadius].d=1.;
  PL.value[9][LJ612EqEnergyDepth].d=1.;
  PL.value[10][LJ612EqRadius].d=0.8;
  PL.value[10][LJ612EqEnergyDepth].d=2.;
  PL.value[11][LJ612EqRadius].d=0.5;
  PL.value[11][LJ612EqEnergyDepth].d=1.;
  copy(PL.value[12],PL.value[10]);
  PL.value[13][LJ612EqRadius].d=1.2;
  PL.value[13][LJ612EqEnergyDepth].d=2.;
  PL.value[14][LJ612EqRadius].d=1.1;
  PL.value[14][LJ612EqEnergyDepth].d=3.;
  copy(PL.value[15],PL.value[11]);
  copy(PL.value[16],PL.value[14]);
  PL.value[17][LJ612EqRadius].d=1.5;
  PL.value[17][LJ612EqEnergyDepth].d=2.;
  for(unsigned int i=9;i<18;++i)  BuildParameterLJ612<double>(PL.value[i]);
  PL.update();
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
  cout<<E<<endl;
  copy(g,0.);
  CalcInteraction(LF,v.structure,PP,g.structure);
  cout<<g<<endl;
  E=0.;
  copy(g,0.);
  CalcInteraction(LF,v.structure,PP,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- list interaction & vector-vector parameter"<<endl;
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
  cout<<E<<endl;
  copy(g,0.);
  CalcInteraction(LF,v.structure,PVV,g.structure);
  cout<<g<<endl;
  E=0.;
  copy(g,0.);
  CalcInteraction(LF,v.structure,PVV,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

