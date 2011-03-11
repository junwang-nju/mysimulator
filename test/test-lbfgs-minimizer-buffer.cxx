
#include "operation/minimize/lbfgs-minimizer-buffer-op.h"
#include "operation/minimize/minimize.h"
#include "operation/minimize/line-minimizer-buffer-base-op.h"
#include "operation/minimize/minimal-step.h"
#include "operation/interaction/calc.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/parameter/build-param-lj612.h"
#include "operation/basic/map-op.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
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

struct TestDistBuffer {
  void renew() {}
};

struct TestInteraction {
  TestDistBuffer  B;
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
  COut<<"Test -- initialize"<<Endl;
  LBFGSMinimizerBuffer<TestInteraction,Vector,TestParameter,
                       double,TrackingLineMinimizerBuffer>   LM;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
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
  COut<<Endl;

  COut<<"Test -- copy"<<Endl;
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
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(LM2);
  COut<<Endl;

  COut<<"Test -- check availability"<<Endl;
  COut<<IsAvailable(LM)<<Endl;
  COut<<IsAvailable(LM2)<<Endl;
  COut<<Endl;

  COut<<"Test -- refer"<<Endl;
  refer(LM2,LM);
  COut<<Endl;

  COut<<"Test -- Minimize"<<Endl;
  COut<<Minimize<StrongWolfe>(LM)<<Endl;
  COut<<LM.MinX<<Endl;
  COut<<LM.MinEnergy()<<Endl;
  COut<<LM.LSearchCount()<<Endl;
  COut<<LM.GCalcCount()<<Endl;
  COut<<Endl;

  COut<<"Test -- minimize over complex data"<<Endl;
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

  Map<Vector<unsigned int>,Vector<UniqueParameter> > PL;
  allocate(PL);
  Vector<unsigned int> key;
  Vector<UniqueParameter> value;
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
  COut<<CSM.MinX<<Endl;
  COut<<CSM.MinEnergy()<<Endl;
  COut<<Minimize<StrongWolfe>(CSM)<<Endl;
  COut<<CSM.MinX<<Endl;
  COut<<CSM.MinEnergy()<<Endl;
  COut<<CSM.LSearchCount()<<Endl;
  COut<<CSM.GCalcCount()<<Endl;
  COut<<Endl;

  return 0;
}

