
#include "interaction-method.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include "property-list.h"
#include <iostream>

using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  InteractionMethod<DistanceEvalDirect,FreeSpace> IM;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(IM);
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  InteractionMethod<DistanceEvalDirect,FreeSpace> IM2;
  allocate(IM2);
  assign(IM2,IM);
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(IM2);
  cout<<endl;

  cout<<"Test - check availability"<<endl;
  cout<<IsAvailable(IM)<<endl;
  cout<<IsAvailable(IM2)<<endl;
  cout<<endl;

  cout<<"Test -- refer"<<endl;
  refer(IM2,IM);
  cout<<endl;

  cout<<"Test -- Set Interaction Method"<<endl;
  Set(IM,PairwiseHarmonic);
  cout<<endl;

  cout<<"Test -- EFunc, GFunc and BFunc"<<endl;
  DistanceEvalDirect DED;
  FreeSpace FS;
  allocate(DED,3,2);
  allocate(FS,3);
  PropertyList<double> v,g;
  unsigned int *sz=new unsigned int[2];
  assign(sz,2,2);
  allocate(v,sz,2);
  allocate(g,sz,2);
  assign(v[0],0.);
  assign(v[1],0.);    v[1][0]=1.3;
  Vector<unsigned int> idx;
  allocate(idx,2);
  idx[0]=0;
  idx[1]=1;
  Vector<UniqueParameter> prm;
  allocate(prm,3);
  prm[HarmonicEqLength]=1.;
  prm[HarmonicEqStrength]=100.;
  GenerateParameterHarmonic(prm);
  double E;
  E=0.;
  IM.EFunc(v.structure,idx(),prm(),2,NULL,0,DED,FS,E);
  cout<<E<<endl;
  assign(g.data,0.,g.size);
  IM.GFunc(v.structure,idx(),prm(),2,NULL,0,DED,FS,g.structure);
  cout<<g<<endl;
  E=0.;
  assign(g.data,0.,g.size);
  IM.BFunc(v.structure,idx(),prm(),2,NULL,0,DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 1;
}

