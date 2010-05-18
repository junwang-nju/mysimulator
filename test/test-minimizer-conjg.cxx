
#include "minimizer-conjg.h"
#include "minimizer-conjg-4propertylist-op.h"
#include "minimizer-line-tracking-4propertylist-op.h"
#include "minimizer-parameter-flat-4propertylist.h"
#include "minimizer-parameter-hierarchy-4propertylist.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {
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
  ConjugateGradientMinimizer<
    PropertyList<double>,
    MinimizerParameter4PropertyListFlat<DistanceEvalDirect,FreeSpace>,
    TrackingLineMinimizer> fLM;
  allocate(fLM);
  buildMinimizer(fLM,Coor,iMask,dMask,DEval,FS,fParamLst,IMLst,fIdxLst);

  cout<<"Test -- minimize with conjg"<<endl;
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

  return 0;
}
