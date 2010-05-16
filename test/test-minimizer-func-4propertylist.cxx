
#include "minimizer-func-4propertylist.h"
#include "minimizer-parameter-flat-4propertylist.h"
#include "minimizer-parameter-hierarchy-4propertylist.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include <iostream>
using namespace std;

int main() {

  Vector<unsigned int> sz;
  PropertyList<double> Coor,Grad;
  allocate(sz,4);
  assign(sz,2);
  allocate(Coor,sz);
  allocate(Grad,sz);
  Coor[0][0]=0;       Coor[0][1]=0;
  Coor[1][0]=0;       Coor[1][1]=1.2;
  Coor[2][0]=1.3;     Coor[2][1]=1.5;
  Coor[3][0]=0.8;     Coor[3][1]=2.2;

  double E;

  cout<<"Test -- func for flat parameter"<<endl;
  MinimizerParameter4PropertyListFlat<DistanceEvalDirect,FreeSpace> PF;
  allocate(sz,4);
  assign(sz,2);
  allocate(PF.iMask,sz(),sz.size);
  allocate(PF.dMask,sz(),sz.size);
  allocate(PF.DEval,2,4);
  allocate(PF.Geo,2);
  allocate(PF.ParamLst,6);
  for(unsigned int i=0;i<3;++i)
    allocate(PF.ParamLst[i],HarmonicNumberParameter);
  for(unsigned int i=3;i<6;++i)
    allocate(PF.ParamLst[i],LJ612NumberParameter);
  allocate(PF.IMLst,6);
  for(unsigned int i=0;i<6;++i) allocate(PF.IMLst[i]);
  for(unsigned int i=0;i<3;++i) Set(PF.IMLst[i],PairwiseHarmonic);
  for(unsigned int i=3;i<6;++i) Set(PF.IMLst[i],PairwiseLJ612);
  allocate(sz,6);
  assign(sz,2);
  allocate(PF.IdxLst,sz(),sz.size);
  finalize(PF);
  PF.ParamLst[0][HarmonicEqLength]=2.;
  PF.ParamLst[0][HarmonicEqStrength]=100.;
  PF.ParamLst[1][HarmonicEqLength]=1.;
  PF.ParamLst[1][HarmonicEqStrength]=100.;
  PF.ParamLst[2][HarmonicEqLength]=0.5;
  PF.ParamLst[2][HarmonicEqStrength]=100.;
  for(unsigned int i=0;i<3;++i) GenerateParameterHarmonic(PF.ParamLst[i]);
  PF.ParamLst[3][LJ612EqRadius]=0.8;
  PF.ParamLst[3][LJ612EqEnergyDepth]=2.;
  PF.ParamLst[4][LJ612EqRadius]=1.1;
  PF.ParamLst[4][LJ612EqEnergyDepth]=3.;
  PF.ParamLst[5][LJ612EqRadius]=0.5;
  PF.ParamLst[5][LJ612EqEnergyDepth]=1.;
  for(unsigned int i=3;i<6;++i) GenerateParameterLJ612(PF.ParamLst[i]);
  PF.IdxLst[0][0]=0;       PF.IdxLst[0][1]=1;
  PF.IdxLst[1][0]=0;       PF.IdxLst[1][1]=2;
  PF.IdxLst[2][0]=0;       PF.IdxLst[2][1]=3;
  PF.IdxLst[3][0]=1;       PF.IdxLst[3][1]=2;
  PF.IdxLst[4][0]=1;       PF.IdxLst[4][1]=3;
  PF.IdxLst[5][0]=2;       PF.IdxLst[5][1]=3;
  E=0;
  EFunc4PropertyList(Coor,E,PF);
  cout<<E<<endl<<endl;
  assign(Grad,0.);
  GFunc4PropertyList(Coor,Grad,PF);
  cout<<Grad<<endl<<endl;
  E=0;
  assign(Grad,0.);
  BFunc4PropertyList(Coor,E,Grad,PF);
  cout<<E<<endl;
  cout<<Grad<<endl<<endl;
  cout<<endl;

  cout<<"Test -- func for hierarchy parameter"<<endl;
  MinimizerParameter4PropertyListHierarchy<DistanceEvalDirect,FreeSpace> PH;
  refer(PH.iMask,PF.iMask);
  refer(PH.dMask,PF.dMask);
  refer(PH.DEval,PF.DEval);
  refer(PH.Geo,PF.Geo);
  allocate(sz,2);
  assign(sz,3);
  allocate(PH.ParamLst,sz);
  for(unsigned int i=0,n=0;i<2;++i)
  for(unsigned int j=0;j<3;++j,++n)
    refer(PH.ParamLst[i][j],PF.ParamLst[n]);
  allocate(PH.IdxLst,sz);
  for(unsigned int i=0,n=0;i<2;++i)
  for(unsigned int j=0;j<3;++j,++n)
    refer(PH.IdxLst[i][j],PF.IdxLst[n]);
  allocate(PH.IMLst,2);
  for(unsigned int i=0;i<2;++i) allocate(PF.IMLst[i]);
  Set(PF.IMLst[0],PairwiseHarmonic);
  Set(PF.IMLst[1],PairwiseLJ612);
  E=0;
  EFunc4PropertyList(Coor,E,PF);
  cout<<E<<endl<<endl;
  assign(Grad,0.);
  GFunc4PropertyList(Coor,Grad,PF);
  cout<<Grad<<endl<<endl;
  E=0;
  assign(Grad,0.);
  BFunc4PropertyList(Coor,E,Grad,PF);
  cout<<E<<endl;
  cout<<Grad<<endl<<endl;
  cout<<endl;
  return 0;
}

