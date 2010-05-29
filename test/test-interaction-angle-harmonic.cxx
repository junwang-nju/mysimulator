
#include "interaction-angle-harmonic.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include "property-list.h"
#include <iostream>
using namespace std;

int main() {

  DistanceEvalDirect DED;
  FreeSpace FS;
  allocate(DED,3,3);
  allocate(FS,3);
  
  PropertyList<double> v,g,tmv;
  Vector<unsigned int> sz;
  allocate(sz,4);
  assign(sz,3);
  allocate(v,sz(),3);
  allocate(g,sz(),3);
  allocate(tmv,sz);
  
  assign(v,0.);
  v[1][0]=1.2;
  v[2][0]=1.5;  v[2][1]=1.; v[2][2]=0.5;
  assign(g,0.);
  assign(tmv,0.);
  
  Vector<unsigned int> idx;
  allocate(idx,3);
  for(unsigned int i=0;i<3;++i) idx[i]=i;
  
  Vector<UniqueParameter> prm;
  allocate(prm,AngleHarmonicNumberParameter);
  prm[AngleHarmonicEqAngle]=2./3.*M_PI;
  prm[AngleHarmonicEqStrength]=20.;
  GenerateParameterAngleHarmonic(prm);
  
  double E;
  cout<<"Test -- calculate Energy of angle"<<endl;
  E=0.;
  EFuncAngleHarmonic(v.structure,idx(),prm(),3,NULL,0,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- calculate Gradient of angle"<<endl;
  assign(g,0.);
  GFuncAngleHarmonic(v.structure,idx(),prm(),3,tmv.structure,4,
                     DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- calculate Energy and Gradient of angle"<<endl;
  E=0.;
  assign(g,0.);
  BFuncAngleHarmonic(v.structure,idx(),prm(),3,tmv.structure,4,
                     DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

