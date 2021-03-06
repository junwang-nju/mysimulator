
#include "operation/minimize/line-minimizer-buffer-base-op.h"
#include "operation/minimize/minimal-step.h"
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
           const double& prm){
  e+=prm*x[0]*x[0];
  g[0]+=2*prm*x[0];
}

struct TestDistBuffer {
  void renew() {}
};

struct TestInteraction {
  TestDistBuffer  B;
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
  LineMinimizerBufferBase<TestInteraction,Vector,TestParameter,double> LM;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  LM.F.EFunc=efunc;
  LM.F.GFunc=gfunc;
  LM.F.BFunc=bfunc;
  TestParameter Pmx;
  Pmx.prm=10.;
  allocate(Pmx.idx,1);
  Vector<double> Coor(1);
  Coor[0]=25.;
  Vector<unsigned int> msk(1);
  Vector<double> dmsk(1);
  msk[0]=1;
  dmsk[0]=1.;
  allocateMinimizerProperty(LM);
  initMinimizerMask(LM,msk,dmsk);
  initMinimizerLocation(LM,Coor,Pmx);
  COut<<Endl;

  COut<<"Test -- assign"<<Endl;
  LineMinimizerBufferBase<TestInteraction,Vector,TestParameter,double> LM2;
  LM2.F.EFunc=efunc;
  LM2.F.GFunc=gfunc;
  LM2.F.BFunc=bfunc;
  Pmx.prm=10.;
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

  COut<<"Test -- generate new location"<<Endl;
  Vector<double> dirc(1);
  dirc[0]=1.;
  double step=0.5;
  ProduceNewLocation(LM2,LM.MinX,dirc,step,LM.RunX,LM.RunE(),LM.RunG,
                     LM.RunPrj());
  COut<<LM.RunX<<"\t"<<LM2.RunE()<<"\t"<<LM.RunG<<"\t"<<LM.RunPrj()<<Endl;
  COut<<Endl;

  COut<<"Test -- minimal step"<<Endl;
  Vector<double> origin(1);
  origin[0]=-2;
  COut<<MinimalStep(LM,origin,dirc)<<Endl;
  COut<<Endl;
  return 1;
}

