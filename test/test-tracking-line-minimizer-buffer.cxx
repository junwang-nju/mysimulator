
#include "data/minimizer/tracking-line-minimizer-buffer.h"
#include "operation/minimize/minimal-step.h"
#include "operation/minimize/line-minimizer-buffer-base-op.h"
#include "operation/minimize/minimize.h"
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
  TrackingLineMinimizerBuffer<TestInteraction,Vector,Vector,double> TLM;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  TLM.F.EFunc=efunc;
  TLM.F.GFunc=gfunc;
  TLM.F.BFunc=bfunc;
  TLM.F.prm=10.;
  Vector<double> Coor(1);
  Coor[0]=25;
  Vector<unsigned int> id(1), msk(1);
  msk[0]=1;
  allocateMinimizerProperty(TLM);
  initMinimizerMask(TLM,msk);
  initMinimizerLocation(TLM,Coor,id);
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  TrackingLineMinimizerBuffer<TestInteraction,Vector,Vector,double> TLM2;
  TLM2.F.EFunc=efunc;
  TLM2.F.GFunc=gfunc;
  TLM2.F.BFunc=bfunc;
  TLM2.F.prm=10.;
  Coor[0]=5;
  msk[0]=0;
  allocateMinimizerProperty(TLM2);
  initMinimizerMask(TLM2,msk);
  initMinimizerLocation(TLM2,Coor,id);
  copy(TLM2,TLM);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(TLM2);
  cout<<endl;

  cout<<"Test - check availability"<<endl;
  cout<<IsAvailable(TLM)<<endl;
  cout<<IsAvailable(TLM2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(TLM2,TLM);
  cout<<endl;

  cout<<"Test -- minimize"<<endl;
  Vector<double> dirc(1);
  dirc[0]=-1.;
  ProduceNewLocation(TLM2,TLM2.MinX,dirc,0,TLM2.MinX,TLM2.MinEnergy(),
                     TLM2.MinG,TLM2.MinProject());
  cout<<Minimize<StrongWolfe>(TLM2,dirc)<<endl;
  cout<<TLM2.MinEnergy()<<endl;
  cout<<TLM2.MinX<<endl;
  cout<<endl;
  
  return 0;
}
