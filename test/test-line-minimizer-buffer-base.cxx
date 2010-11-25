
#include "operation/minimize/line-minimizer-buffer-base-op.h"
#include "operation/minimize/minimal-step.h"
#include <iostream>
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

struct TestInteraction {
  double prm;
  void (*EFunc)(const Vector<double>&,double&,const double&);
  void (*GFunc)(const Vector<double>&,Vector<double>&,const double&);
  void (*BFunc)(const Vector<double>&,double&,Vector<double>&,const double&);
  ~TestInteraction() {}
};

void CalcInteraction(TestInteraction& TI,const Vector<double>& X,
                     const Vector<unsigned int>& ID, double& E) {
  TI.EFunc(X,E,TI.prm);
}
void CalcInteraction(TestInteraction& TI,const Vector<double>& X,
                     const Vector<unsigned int>& ID, Vector<double>& G) {
  TI.GFunc(X,G,TI.prm);
}
void CalcInteraction(TestInteraction& TI,const Vector<double>& X,
                     const Vector<unsigned int>& ID,
                     double& E, Vector<double>& G) {
  TI.BFunc(X,E,G,TI.prm);
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
  LineMinimizerBufferBase<TestInteraction,Vector,Vector,double> LM;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  LM.F.EFunc=efunc;
  LM.F.GFunc=gfunc;
  LM.F.BFunc=bfunc;
  LM.F.prm=10.;
  Vector<double> Coor(1);
  Coor[0]=25.;
  Vector<unsigned int> id(1),msk(1);
  msk[0]=1;
  allocateMinimizerProperty(LM);
  initMinimizerMask(LM,msk);
  initMinimizerLocation(LM,Coor,id);
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  LineMinimizerBufferBase<TestInteraction,Vector,Vector,double> LM2;
  LM2.F.EFunc=efunc;
  LM2.F.GFunc=gfunc;
  LM2.F.BFunc=bfunc;
  LM2.F.prm=10.;
  allocateMinimizerProperty(LM2);
  initMinimizerMask(LM2,msk);
  initMinimizerLocation(LM2,Coor,id);
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

  cout<<"Test -- generate new location"<<endl;
  Vector<double> dirc(1);
  dirc[0]=1.;
  double step=0.5;
  ProduceNewLocation(LM2,LM.MinX,dirc,step,LM.RunX,LM.RunE(),LM.RunG,
                      LM.RunPrj());
  cout<<LM.RunX<<"\t"<<LM2.RunE()<<"\t"<<LM.RunG<<"\t"<<LM.RunPrj()<<endl;
  cout<<endl;

  cout<<"Test -- minimal step"<<endl;
  Vector<double> origin(1);
  origin[0]=-2;
  cout<<MinimalStep(LM,origin,dirc)<<endl;
  cout<<endl;
  return 1;
}

