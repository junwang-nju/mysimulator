
#include "operation/minimize/minimizer-buffer-base-op.h"
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
  MinimizerBufferBase<TestInteraction,Vector,TestParameter,double> MB;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  MB.F.EFunc=efunc;
  MB.F.GFunc=gfunc;
  MB.F.BFunc=bfunc;
  TestParameter Pmx;
  Pmx.prm=10;
  allocate(Pmx.idx,1);
  Vector<double> Coor(1);
  Coor[0]=25;
  Vector<unsigned int> msk(1);
  Vector<double> dmsk(1);
  msk[0]=1;
  dmsk[0]=1;
  allocateMinimizerProperty(MB);
  initMinimizerMask(MB,msk,dmsk);
  initMinimizerLocation(MB,Coor,Pmx);
  COut<<Endl;

  COut<<"Test -- assign"<<Endl;
  MinimizerBufferBase<TestInteraction,Vector,TestParameter,double> MB2;
  MB2.F.EFunc=efunc;
  MB2.F.GFunc=gfunc;
  MB2.F.BFunc=bfunc;
  Pmx.prm=10;
  allocateMinimizerProperty(MB2);
  initMinimizerMask(MB2,msk,dmsk);
  initMinimizerLocation(MB2,Coor,Pmx);
  copy(MB2,MB);
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(MB2);
  COut<<Endl;

  COut<<"Test -- check avaialability"<<Endl;
  COut<<IsAvailable(MB)<<Endl;
  COut<<IsAvailable(MB2)<<Endl;
  COut<<Endl;

  COut<<"Test -- refer"<<Endl;
  refer(MB2,MB);
  COut<<Endl;

  COut<<"Test -- Generate new Location"<<Endl;
  double desty,destp;
  Vector<double> dest(1),destg(1);
  Vector<double> dirc(1);
  dirc[0]=1.;
  double step=0.5;
  ProduceNewLocation(MB2,MB.MinX,dirc,step,dest,desty,destg,destp);
  COut<<dest<<"\t"<<desty<<"\t"<<destg<<"\t"<<destp<<Endl;
  COut<<Endl;

  return 1;
}

