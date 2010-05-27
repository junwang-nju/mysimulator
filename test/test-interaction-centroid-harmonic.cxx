
#include "interaction-centroid-harmonic.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include "property-list.h"
#include <iostream>
using namespace std;

int main() {

  DistanceEvalDirect DED;
  FreeSpace FS;
  allocate(DED,3,2);
  allocate(FS,3);

  PropertyList<double> v,g;
  unsigned int *sz=new unsigned int[5];
  assign(sz,2,5);
  allocate(v,sz,5);
  allocate(g,sz,5);
  assign(v[0],0.);
  assign(v[1],0.);    v[1][0]=1.3;
  assign(v[2],1.);
  assign(v[3],2.);    v[3][0]=0.3;
  assign(v[4],0.5);   v[4][0]=-1.7;

  Vector<unsigned int> idx;
  allocate(idx,9);
  for(unsigned int i=0;i<5;++i) idx[i]=i;
  idx[5]=0;
  idx[6]=2;
  idx[7]=2;
  idx[8]=3;

  Vector<UniqueParameter> prm;
  allocate(prm,HarmonicNumberParameter);
  prm[CentroidHarmonicEqLength]=1.;
  prm[CentroidHarmonicEqStrength]=100.;
  GenerateParameterHarmonic(prm);

  PropertyList<double> tmv;
  Vector<unsigned int> vsz;
  allocate(vsz,2);
  assign(vsz,2);
  allocate(tmv,vsz);

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncCentroidHarmonic(v.structure,idx(),prm(),9,tmv.structure,2,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  assign(g.data,0.,g.size);
  GFuncCentroidHarmonic(v.structure,idx(),prm(),9,tmv.structure,2,
                        DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  assign(g.data,0.,g.size);
  BFuncCentroidHarmonic(v.structure,idx(),prm(),9,tmv.structure,2,
                        DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 1;
}

