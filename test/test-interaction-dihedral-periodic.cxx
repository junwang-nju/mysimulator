
#include "interaction-dihedral-periodic.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include "property-list.h"
#include <iostream>
using namespace std;
  
int main() {
  DistanceEvalDirect DED;
  FreeSpace FS;
  allocate(DED,3,4);
  allocate(FS,3);
  
  PropertyList<double> v,g,tmv;
  Vector<unsigned int> sz;
  allocate(sz,6);
  assign(sz,3);
  allocate(v,sz(),4);
  allocate(g,sz(),4);
  allocate(tmv,sz);
  
  assign(v,0.);
  v[0][0]=-1.;    v[0][1]=-2.;
  v[2][0]=3;
  v[3][0]=4;      v[3][1]=2.;       v[3][2]=2.;
  
  Vector<unsigned int> Idx;
  allocate(Idx,4);
  for(unsigned int i=0;i<4;++i) Idx[i]=i;
  
  Vector<UniqueParameter> prm;
  allocateDihedralPeriodicParameter(prm,2);
  prm[1+DihedralPeriodicStrength]=1.;
  prm[1+DihedralPeriodicFrequence]=1.;
  prm[1+DihedralPeriodicPhase]=0.5*M_PI;
  prm[5+DihedralPeriodicStrength]=0.5;
  prm[5+DihedralPeriodicFrequence]=3.;
  prm[5+DihedralPeriodicPhase]=0.5*M_PI;
  GenerateParameterDihedralPeriodic(prm);
  
  double E;
  
  cout<<"Test -- calculate energy"<<endl;
  E=0.;
  EFuncDihedralPeriodic(v.structure,Idx(),prm(),4,tmv.structure,6,
                        DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- calculate gradient"<<endl;
  assign(g,0.);
  GFuncDihedralPeriodic(v.structure,Idx(),prm(),4,tmv.structure,6,
                        DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- calculate energy and gradient"<<endl;
  E=0.;
  assign(g,0.);
  BFuncDihedralPeriodic(v.structure,Idx(),prm(),4,tmv.structure,6,
                        DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}
