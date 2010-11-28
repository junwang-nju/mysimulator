
#include "operation/minimize/steep-minimizer-buffer-op.h"
#include "operation/minimize/minimize.h"
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
  SteepestDescentMinimizerBuffer<TestInteraction,Vector,Vector,double,
                                 TrackingLineMinimizerBuffer> SM;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  SM.F.EFunc=efunc;
  SM.F.GFunc=gfunc;
  SM.F.BFunc=bfunc;
  SM.F.prm=10.;
  Vector<double> Coor(1);
  Coor[0]=25;
  Vector<unsigned int> id(1), msk(1);
  msk[0]=1;
  allocateMinimizerProperty(SM);
  initMinimizerMask(SM,msk);
  initMinimizerLocation(SM,Coor,id);
  cout<<endl;

  cout<<"Test -- copy"<<endl;
  SteepestDescentMinimizerBuffer<TestInteraction,Vector,Vector,double,
                                 TrackingLineMinimizerBuffer> SM2;
  SM2.F.EFunc=efunc;
  SM2.F.GFunc=gfunc;
  SM2.F.BFunc=bfunc;
  SM2.F.prm=10.;
  Coor[0]=5;
  msk[0]=0;
  allocateMinimizerProperty(SM2);
  initMinimizerMask(SM2,msk);
  initMinimizerLocation(SM2,Coor,id);
  copy(SM2,SM);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(SM2);
  cout<<endl;

  cout<<"Test -- check availability"<<endl;
  cout<<IsAvailable(SM)<<endl;
  cout<<IsAvailable(SM2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(SM2,SM);
  cout<<endl;

  cout<<"Test -- minimize"<<endl;
  cout<<Minimize<StrongWolfe>(SM)<<endl;
  cout<<SM.MinX<<endl;
  cout<<SM.MinEnergy()<<endl;
  cout<<SM.LSearchCount()<<endl;
  cout<<SM.GCalcCount()<<endl;
  cout<<endl;

  return 0;
}
