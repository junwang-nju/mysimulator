
#include "operation/interaction/interaction-calc.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/parameter/build-param-lj612.h"
#include "data/derived/parameter-list.h"
using namespace std;

int main() {
  cout<<"Test -- initialize interaction"<<endl;
  Interaction<double,DistanceBufferSimple,FreeSpace> F;
  cout<<endl;
  
  cout<<"Test -- allocate Interaction"<<endl;
  allocate(F,Harmonic,3,2);
  cout<<endl;

  cout<<"Test -- copy Interaction"<<endl;
  Interaction<double,DistanceBufferSimple,FreeSpace> F2;
  allocate(F2,Harmonic,3,2);
  copy(F2,F);
  cout<<endl;
  
  cout<<"Test -- refer Interaction"<<endl;
  Interaction<double,DistanceBufferSimple,FreeSpace> F3;
  refer(F3,F);
  cout<<endl;

  cout<<"Test -- release Interaction"<<endl;
  release(F2);
  cout<<endl;
  
  cout<<"Test - Interaction Calc"<<endl;
  F.prm[HarmonicEqLength].d=1.;
  F.prm[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(F.prm);
  Vector<unsigned int> sz(2);
  copy(sz,3);
  PropertyList<double> v,g;
  allocate(v,sz);
  allocate(g,sz);
  copy(v,0.);
  v[1][0]=1.3;
  Vector<unsigned int> idx(2);
  idx[0]=0; idx[1]=1;
  double E;
  E=0;
  CalcInteraction(F,v.structure,idx.data,E);
  cout<<E<<endl;
  copy(g,0.);
  CalcInteraction(F,v.structure,idx.data,g.structure);
  cout<<g<<endl;
  E=0.;
  copy(g,0.);
  CalcInteraction(F,v.structure,idx.data,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- initialize List Interaction"<<endl;
  ListInteraction<double,DistanceBufferSimple,FreeSpace> LF;
  cout<<endl;

  cout<<"Test -- allocate List Interaction"<<endl;
  allocate(LF,Harmonic,3,2,6);
  cout<<endl;

  cout<<"Test -- copy List Interaction"<<endl;
  ListInteraction<double,DistanceBufferSimple,FreeSpace> LF2;
  allocate(LF2,Harmonic,3,2,6);
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
  allocate(sz,4);
  copy(sz,3);
  allocate(v,sz);
  allocate(g,sz);
  copy(v,0.);
  v[1][1]=1.2;
  v[2][0]=1.3;    v[2][1]=1.5;
  v[3][0]=0.8;    v[3][1]=2.2;
  PropertyList<unsigned int> lidx;
  allocate(sz,6);
  copy(sz,2);
  allocate(lidx,sz);
  lidx[0][0]=0;     lidx[0][1]=1;
  lidx[1][0]=0;     lidx[1][1]=2;
  lidx[2][0]=0;     lidx[2][1]=3;
  lidx[3][0]=1;     lidx[3][1]=2;
  lidx[4][0]=1;     lidx[4][1]=3;
  lidx[5][0]=2;     lidx[5][1]=3;
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
  for(unsigned int i=0;i<LF.NumList();++i) {
    sz[0]=Harmonic;
    sz[1]=Kind[lidx[i][0]];
    sz[2]=Kind[lidx[i][1]];
    refer(LF.prm[i],*get(PL,sz));
  }
  E=0.;
  CalcInteraction(LF,v.structure,lidx.structure,E);
  cout<<E<<endl;
  copy(g,0);
  CalcInteraction(LF,v.structure,lidx.structure,g.structure);
  cout<<g<<endl;
  copy(g,0);
  E=0.;
  CalcInteraction(LF,v.structure,lidx.structure,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- Interaction Vector Calculation"<<endl;
  Vector<Interaction<double,DistanceBufferSimple,FreeSpace> > VF;
  allocate(VF,6);
  for(unsigned int i=0;i<3;++i)   allocate(VF[i],Harmonic,3,2);
  for(unsigned int i=3;i<6;++i)   allocate(VF[i],LJ612,3,2);
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
    sz[1]=Kind[lidx[i][0]];
    sz[2]=Kind[lidx[i][1]];
    refer(VF[i].prm,*get(PL,sz));
  }
  for(unsigned int i=3;i<6;++i) {
    sz[0]=LJ612;
    sz[1]=Kind[lidx[i][0]];
    sz[2]=Kind[lidx[i][1]];
    refer(VF[i].prm,*get(PL,sz));
  }
  E=0.;
  CalcInteraction(VF,v.structure,lidx.structure,E);
  cout<<E<<endl;
  copy(g,0.);
  CalcInteraction(VF,v.structure,lidx.structure,g.structure);
  cout<<g<<endl;
  E=0.;
  copy(g,0.);
  CalcInteraction(VF,v.structure,lidx.structure,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- List Interaction Vector CalcInteraction"<<endl;
  Vector<ListInteraction<double,DistanceBufferSimple,FreeSpace> > VLF;
  allocate(VLF,2);
  allocate(VLF[0],Harmonic,3,2,3);
  allocate(VLF[1],LJ612,3,2,3);
  Vector<PropertyList<unsigned int> > vlidx(2);
  allocate(sz,3);
  copy(sz,2);
  allocate(vlidx[0],sz);
  allocate(vlidx[1],sz);
  vlidx[0][0][0]=0;     vlidx[0][0][1]=1;
  vlidx[0][1][0]=0;     vlidx[0][1][1]=2;
  vlidx[0][2][0]=0;     vlidx[0][2][1]=3;
  vlidx[1][0][0]=1;     vlidx[1][0][1]=2;
  vlidx[1][1][0]=1;     vlidx[1][1][1]=3;
  vlidx[1][2][0]=2;     vlidx[1][2][1]=3;
  for(unsigned int i=0;i<3;i++)   refer(VLF[0].prm[i],VF[i].prm);
  for(unsigned int i=0;i<3;i++)   refer(VLF[1].prm[i],VF[i+3].prm);
  E=0.;
  CalcInteraction(VLF,v.structure,vlidx.data,E);
  cout<<E<<endl;
  copy(g,0);
  CalcInteraction(VLF,v.structure,vlidx.data,g.structure);
  cout<<g<<endl;
  E=0.;
  copy(g,0);
  CalcInteraction(VLF,v.structure,vlidx.data,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

