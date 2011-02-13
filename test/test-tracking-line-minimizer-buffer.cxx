
#include "data/minimizer/tracking-line-minimizer-buffer.h"
#include "operation/minimize/minimal-step.h"
#include "operation/minimize/line-minimizer-buffer-base-op.h"
#include "operation/minimize/minimize.h"
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
  TestDistBuffer B;
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
  TrackingLineMinimizerBuffer<TestInteraction,Vector,TestParameter,double> TLM;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  TLM.F.EFunc=efunc;
  TLM.F.GFunc=gfunc;
  TLM.F.BFunc=bfunc;
  TestParameter Pmx;
  Pmx.prm=10.;
  allocate(Pmx.idx,1);
  Vector<double> Coor(1);
  Coor[0]=25;
  Vector<unsigned int> msk(1);
  Vector<double> dmsk(1);
  msk[0]=1;
  dmsk[0]=1.;
  allocateMinimizerProperty(TLM);
  initMinimizerMask(TLM,msk,dmsk);
  COut<<Coor<<Endl;
  initMinimizerLocation(TLM,Coor,Pmx);
  COut<<Endl;

  COut<<"Test -- assign"<<Endl;
  TrackingLineMinimizerBuffer<TestInteraction,Vector,TestParameter,double> TLM2;
  TLM2.F.EFunc=efunc;
  TLM2.F.GFunc=gfunc;
  TLM2.F.BFunc=bfunc;
  Pmx.prm=10.;
  Coor[0]=5;
  msk[0]=0;
  allocateMinimizerProperty(TLM2);
  initMinimizerMask(TLM2,msk,dmsk);
  initMinimizerLocation(TLM2,Coor,Pmx);
  copy(TLM2,TLM);
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(TLM2);
  COut<<Endl;

  COut<<"Test - check availability"<<Endl;
  COut<<IsAvailable(TLM)<<Endl;
  COut<<IsAvailable(TLM2)<<Endl;
  COut<<Endl;

  COut<<"Test -- refer"<<Endl;
  refer(TLM2,TLM);
  COut<<Endl;

  COut<<"Test -- minimize"<<Endl;
  Vector<double> dirc(1);
  dirc[0]=-1.;
  ProduceNewLocation(TLM2,TLM2.MinX,dirc,0,TLM2.MinX,TLM2.MinEnergy(),
                     TLM2.MinG,TLM2.MinProject());
  COut<<Minimize<StrongWolfe>(TLM2,dirc)<<Endl;
  COut<<TLM2.MinEnergy()<<Endl;
  COut<<TLM2.MinX<<Endl;
  COut<<Endl;
  
  return 0;
}
