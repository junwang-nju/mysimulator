
#include "interaction-pairwise-lj1012cut.h"
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
  allocate(prm,LJ1012CutNumberParameter);
  prm[LJ1012CutEqRadius]=1.;
  prm[LJ1012CutEqEnergyDepth]=2.;
  prm[LJ1012CutCutR]=1.6;
  GenerateParameterLJ1012Cut(prm);

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncPairwiseLJ1012Cut(v.structure,idx(),prm(),2,NULL,0,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  assign(g.data,0.,g.size);
  GFuncPairwiseLJ1012Cut(v.structure,idx(),prm(),2,NULL,0,DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  assign(g.data,0.,g.size);
  BFuncPairwiseLJ1012Cut(v.structure,idx(),prm(),2,NULL,0,DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

