
#include "operation/minimize/lbfgs-minimizer-buffer-op.h"
#include "operation/minimize/minimize.h"
#include "operation/minimize/line-minimizer-buffer-base-op.h"
#include "operation/minimize/minimal-step.h"
#include "operation/interaction/calc.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/parameter/build-param-lj612.h"
#include "data/derived/parameter-list.h"
#include <iostream>
using namespace std;

void efunc(const Vector<double>& x, double& e, const double& prm) {
  e+=prm*x[0]*x[0];
}

void gfunc(const Vector<double>& x, Vector<double>& g, const double& prm) {
  g[0]+=2*prm*x[0];
}

void bfunc(const Vector<double>& x, double& e, Vector<double>& g,
           const double& prm) {
  e+=prm*x[0]*x[0];
  g[0]+=2*prm*x[0];
}

struct TestInteraction {
  double prm;
  void (*EFunc)(const Vector<double>&,double&,const double&);
  void (*GFunc)(const Vector<double>&,Vector<double>&,const double&);
  void (*BFunc)(const Vector<double>&,double&,Vector<double>&,const double&);
  ~TestInteraction() {}
};

struct TestParameter {
  double prm;
  Vector<unsigned int> idx;
};

bool IsAvailable(const TestParameter& P) { return IsAvailable(P.idx); }
void release(TestParameter& P) { release(P.idx); }
void copy(TestParameter& P, const TestParameter& cP) {
  copy(P.prm,cP.prm);
  copy(P.idx,cP.idx);
}
void refer(TestParameter& P, const TestParameter& cP) {
  refer(P.idx,cP.idx);
}
void imprint(TestParameter& P, const TestParameter& cP) {
  imprint(P.idx,cP.idx);
}

void CalcInteraction(TestInteraction& TI,const Vector<double>& X,
                     const TestParameter& P, double& E) {
  TI.EFunc(X,E,P.prm);
}
void CalcInteraction(TestInteraction& TI,const Vector<double>& X,
                     const TestParameter& P, Vector<double>& G) {
  TI.GFunc(X,G,P.prm);
}
void CalcInteraction(TestInteraction& TI,const Vector<double>& X,
                     const TestParameter& P,
                     double& E, Vector<double>& G) {
  TI.BFunc(X,E,G,P.prm);
}
void release(TestInteraction& TI) {}
void copy(TestInteraction& TI, const TestInteraction& cTI) {
  TI.prm=cTI.prm;
  TI.EFunc=cTI.EFunc;
  TI.GFunc=cTI.GFunc;
  TI.BFunc=cTI.BFunc;
}
bool IsAvailable(const TestInteraction& TI) { return true; }
void refer(TestInteraction& TI, const TestInteraction& cTI) {
  copy(TI,cTI);
}

int main() {
  cout<<"Test -- initialize"<<endl;
  LBFGSMinimizerBuffer<TestInteraction,Vector,TestParameter,
                       double,TrackingLineMinimizerBuffer>   LM;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  LM.F.EFunc=efunc;
  LM.F.GFunc=gfunc;
  LM.F.BFunc=bfunc;
  Vector<double> Coor(1);
  Coor[0]=25.;
  TestParameter Pmx;
  Pmx.prm=10.;
  allocate(Pmx.idx,1);
  Vector<unsigned int> msk(1);
  Vector<double> dmsk(1);
  msk[0]=1;
  dmsk[0]=1.;
  allocateMinimizerProperty(LM);
  initMinimizerMask(LM,msk,dmsk);
  initMinimizerLocation(LM,Coor,Pmx);
  cout<<endl;

  cout<<"Test -- copy"<<endl;
  LBFGSMinimizerBuffer<TestInteraction,Vector,TestParameter,double,
                       TrackingLineMinimizerBuffer>   LM2;
  LM2.F.EFunc=efunc;
  LM2.F.GFunc=gfunc;
  LM2.F.BFunc=bfunc;
  Pmx.prm=10.;
  Coor[0]=2.;
  msk[0]=0;
  allocateMinimizerProperty(LM2);
  initMinimizerMask(LM2,msk,dmsk);
  initMinimizerLocation(LM2,Coor,Pmx);
  copy(LM2,LM);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(LM2);
  cout<<endl;

  cout<<"Test -- check availability"<<endl;
  cout<<IsAvailable(LM)<<endl;
  cout<<IsAvailable(LM2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(LM2,LM);
  cout<<endl;

  cout<<"Test -- Minimize"<<endl;
  cout<<Minimize<StrongWolfe>(LM)<<endl;
  cout<<LM.MinX<<endl;
  cout<<LM.MinEnergy()<<endl;
  cout<<LM.LSearchCount()<<endl;
  cout<<LM.GCalcCount()<<endl;
  cout<<endl;

  cout<<"Test -- minimize over complex data"<<endl;
  LBFGSMinimizerBuffer<
      ListInteraction<double,DistanceBufferSimple,FreeSpace>,
      PropertyList,Vector<InteractionParameterUnit>,double,
      TrackingLineMinimizerBuffer> CSM;
  Vector<unsigned int> sz;
  allocate(sz,6);
  for(unsigned int i=0;i<3;++i) sz[i]=Harmonic;
  for(unsigned int i=3;i<6;++i) sz[i]=LJ612;
  allocate(CSM.F,sz,3,4);
  Vector<InteractionParameterUnit> RP(6);
  for(unsigned int i=0;i<3;++i) allocate(RP[i],Harmonic);
  for(unsigned int i=3;i<6;++i) allocate(RP[i],LJ612);
  ParameterList PL;
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
  Vector<unsigned int> Kind(4);
  copy(Kind,0);
  Kind[1]=1;
  Kind[3]=2;
  RP[0].idx[0]=0;    RP[0].idx[1]=1;
  RP[1].idx[0]=0;    RP[1].idx[1]=2;
  RP[2].idx[0]=0;    RP[2].idx[1]=3;
  RP[3].idx[0]=1;    RP[3].idx[1]=2;
  RP[4].idx[0]=1;    RP[4].idx[1]=3;
  RP[5].idx[0]=2;    RP[5].idx[1]=3;
  allocate(sz,3);
  for(unsigned int i=0;i<3;++i) {
    sz[0]=Harmonic;
    sz[1]=Kind[RP[i].idx[0]];
    sz[2]=Kind[RP[i].idx[1]];
    refer(RP[i].prm,*get(PL,sz));
  }
  for(unsigned int i=3;i<6;++i) {
    sz[0]=LJ612;
    sz[1]=Kind[RP[i].idx[0]];
    sz[2]=Kind[RP[i].idx[1]];
    refer(RP[i].prm,*get(PL,sz));
  }
  PropertyList<double> cv;
  allocate(sz,4);
  copy(sz,3);
  allocate(cv,sz);
  copy(cv,0.);
  cv[1][1]=1.2;
  cv[2][0]=1.3;    cv[2][1]=1.5;
  cv[3][0]=0.8;    cv[3][1]=2.2;      cv[3][2]=1;
  allocateMinimizerProperty(CSM);
  PropertyList<unsigned int> cimsk;
  PropertyList<double> cdmsk;
  allocate(cimsk,sz);
  allocate(cdmsk,sz);
  copy(cimsk,1);
  copy(cimsk[0],0);
  copy<double,unsigned int>(cdmsk,cimsk);
  initMinimizerMask(CSM,cimsk,cdmsk);
  initMinimizerLocation(CSM,cv,RP);
  cout<<CSM.MinX<<endl;
  cout<<CSM.MinEnergy()<<endl;
  cout<<Minimize<StrongWolfe>(CSM)<<endl;
  cout<<CSM.MinX<<endl;
  cout<<CSM.MinEnergy()<<endl;
  cout<<CSM.LSearchCount()<<endl;
  cout<<CSM.GCalcCount()<<endl;
  cout<<endl;

  return 0;
}
