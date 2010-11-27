
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

  /*
  Vector<unsigned int> sz;

  PropertyList<double> Coor;
  allocate(sz,4);
  assign(sz,2);
  allocate(Coor,sz);
  Coor[0][0]=0;       Coor[0][1]=0;
  Coor[1][0]=0;       Coor[1][1]=1.2;
  Coor[2][0]=1.3;     Coor[2][1]=1.5;
  Coor[3][0]=0.8;     Coor[3][1]=2.2;

  PropertyList<unsigned int> iMask;
  PropertyList<double> dMask;
  allocate(iMask,sz);
  allocate(dMask,sz);
  assign(iMask,1);
  assign(dMask,1);
  
  DistanceEvalDirect DEval;
  FreeSpace FS;
  allocate(DEval,2,4);
  allocate(FS,2);
  
  Vector<InteractionMethod<DistanceEvalDirect,FreeSpace> > IMLst;

  allocate(IMLst,6);
  for(unsigned int i=0;i<6;++i) allocate(IMLst[i]);
  for(unsigned int i=0;i<3;++i) Set(IMLst[i],PairwiseHarmonic);
  for(unsigned int i=3;i<6;++i) Set(IMLst[i],PairwiseLJ612);
  Vector<Vector<UniqueParameter> > fParamLst;
  allocate(fParamLst,6);
  for(unsigned int i=0;i<3;++i) allocate(fParamLst[i],HarmonicNumberParameter);
  for(unsigned int i=3;i<6;++i) allocate(fParamLst[i],LJ612NumberParameter);
  PropertyList<unsigned int> fIdxLst;
  allocate(sz,6);
  assign(sz,2);
  allocate(fIdxLst,sz);
  fParamLst[0][HarmonicEqLength]=2.;
  fParamLst[0][HarmonicEqStrength]=100.;
  fParamLst[1][HarmonicEqLength]=1.;
  fParamLst[1][HarmonicEqStrength]=100.;
  fParamLst[2][HarmonicEqLength]=0.5;
  fParamLst[2][HarmonicEqStrength]=100.;
  for(unsigned int i=0;i<3;++i) GenerateParameterHarmonic(fParamLst[i]);
  fParamLst[3][LJ612EqRadius]=0.8;
  fParamLst[3][LJ612EqEnergyDepth]=2.;
  fParamLst[4][LJ612EqRadius]=1.1;
  fParamLst[4][LJ612EqEnergyDepth]=3.;
  fParamLst[5][LJ612EqRadius]=0.5;
  fParamLst[5][LJ612EqEnergyDepth]=1.;
  for(unsigned int i=3;i<6;++i) GenerateParameterLJ612(fParamLst[i]);
  fIdxLst[0][0]=0;       fIdxLst[0][1]=1;
  fIdxLst[1][0]=0;       fIdxLst[1][1]=2;
  fIdxLst[2][0]=0;       fIdxLst[2][1]=3;
  fIdxLst[3][0]=1;       fIdxLst[3][1]=2;
  fIdxLst[4][0]=1;       fIdxLst[4][1]=3;
  fIdxLst[5][0]=2;       fIdxLst[5][1]=3;
  SteepestDescentMinimizer<
    PropertyList<double>,
    MinimizerParameter4PropertyListFlat<DistanceEvalDirect,FreeSpace>,
    TrackingLineMinimizer> fLM;
  allocate(fLM);
  buildMinimizer(fLM,Coor,iMask,dMask,DEval,FS,fParamLst,IMLst,fIdxLst);

  cout<<"Test -- minimize with steep"<<endl;
  cout<<"Before minimize:"<<endl;
  cout<<*(fLM.MinEnergy)<<endl;
  cout<<*(fLM.MinCoor)<<endl;
  cout<<endl;
  cout<<"Minimize flag:"<<fLM.Minimize<StrongWolfe>()<<endl;
  cout<<endl;
  cout<<"After minimize"<<endl;
  cout<<*(fLM.MinEnergy)<<endl;
  cout<<*(fLM.MinCoor)<<endl;
  cout<<endl;
  cout<<*(fLM.LineSearchCount)<<endl;
  cout<<*(fLM.GCalcCount)<<endl;
  cout<<endl;
  */

  return 0;
}
