
#include "operation/interaction/dihedral-periodic.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-dihedral-periodic.h"
#include "data/basic/property-list.h"
#include <iostream>
using namespace std;
  
int main() {
  DistanceBufferSimple<double> DED;
  FreeSpace FS;
  allocate(DED,3,4);
  allocate(FS,3);
  
  PropertyList<double> v,g,tmv;
  Vector<unsigned int> sz;
  allocate(sz,4);
  copy(sz,3);
  allocate(v,sz);
  allocate(g,sz);
  allocate(sz,6);
  copy(sz,3);
  allocate(tmv,sz);
  
  copy(v,0.);
  v[0][0]=-1.;    v[0][1]=-2.;
  v[2][0]=3;
  v[3][0]=4;      v[3][1]=2.;       v[3][2]=2.;
  
  Vector<unsigned int> Idx;
  allocate(Idx,4);
  for(unsigned int i=0;i<4;++i) Idx[i]=i;
  
  Vector<UniqueParameter> prm;
  allocateDihPeriodicParameter(prm,2);
  prm[2+DihPeriodicStrength].d=1.;
  prm[2+DihPeriodicFrequence].d=1.;
  prm[2+DihPeriodicPhase].d=0.5*M_PI;
  prm[6+DihPeriodicStrength].d=0.5;
  prm[6+DihPeriodicFrequence].d=3.;
  prm[6+DihPeriodicPhase].d=0.5*M_PI;
  BuildParameterDihPeriodic<double>(prm);
  double E;
  
  cout<<"Test -- calculate energy"<<endl;
  E=0.;
  EFuncDihPeriodic(v.structure,Idx(),prm(),DED,FS,E,tmv.structure);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- calculate gradient"<<endl;
  copy(g,0.);
  GFuncDihPeriodic(v.structure,Idx(),prm(),DED,FS,g.structure,tmv.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- calculate energy and gradient"<<endl;
  E=0.;
  copy(g,0.);
  BFuncDihPeriodic(v.structure,Idx(),prm(),DED,FS,E,g.structure,tmv.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}
