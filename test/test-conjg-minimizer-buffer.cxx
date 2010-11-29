
#include "operation/minimize/conjg-minimizer-buffer-op.h"
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
  ConjugateGradientMinimizerBuffer<TestInteraction,Vector,Vector,double,
                                   TrackingLineMinimizerBuffer> CM;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  CM.F.EFunc=efunc;
  CM.F.GFunc=gfunc;
  CM.F.BFunc=bfunc;
  CM.F.prm=10.;
  Vector<double> Coor(1);
  Coor[0]=25.;
  Vector<unsigned int> id(1), msk(1);
  Vector<double> dmsk(1);
  msk[0]=1;
  dmsk[0]=1.;
  allocateMinimizerProperty(CM);
  initMinimizerMask(CM,msk,dmsk);
  initMinimizerLocation(CM,Coor,id);
  cout<<endl;

  cout<<"Test -- copy"<<endl;
  ConjugateGradientMinimizerBuffer<TestInteraction,Vector,Vector,double,
                                   TrackingLineMinimizerBuffer> CM2;
  CM2.F.EFunc=efunc;
  CM2.F.GFunc=gfunc;
  CM2.F.BFunc=bfunc;
  CM2.F.prm=10.;
  Coor[0]=2.;
  msk[0]=0;
  allocateMinimizerProperty(CM2);
  initMinimizerMask(CM2,msk,dmsk);
  initMinimizerLocation(CM2,Coor,id);
  copy(CM2,CM);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(CM2);
  cout<<endl;

  cout<<"Test -- check availability"<<endl;
  cout<<IsAvailable(CM)<<endl;
  cout<<IsAvailable(CM2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(CM2,CM);
  cout<<endl;

  cout<<"Test -- minimize"<<endl;
  cout<<Minimize<StrongWolfe>(CM)<<endl;
  cout<<CM.MinX<<endl;
  cout<<CM.MinEnergy()<<endl;
  cout<<CM.LSearchCount()<<endl;
  cout<<CM.GCalcCount()<<endl;
  cout<<endl;

  return 0;
}
