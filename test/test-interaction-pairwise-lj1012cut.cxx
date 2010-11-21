
#include "operation/interaction/lj1012cut.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-lj1012cut.h"
#include <iostream>
using namespace std;

int main() {

  DistanceBufferSimple<double> DED;
  FreeSpace FS;
  allocate(DED,3,2);
  allocate(FS,3);

  PropertyList<double> v,g;
  Vector<unsigned int> sz(2);
  copy(sz,3);
  allocate(v,sz);
  allocate(g,sz);
  copy(v[0],0.);
  copy(v[1],0.);    v[1][0]=1.3;

  Vector<unsigned int> idx;
  allocate(idx,2);
  idx[0]=0;
  idx[1]=1;

  Vector<UniqueParameter> prm;
  allocate(prm,LJ1012CutNumberParameter);
  prm[LJ1012CutEqRadius].d=1.;
  prm[LJ1012CutEqEnergyDepth].d=2.;
  prm[LJ1012CutCutR].d=1.6;
  BuildParameterLJ1012Cut<double>(prm);

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncLJ1012Cut(v.structure,idx.data,prm.data,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  copy(g,0.);
  GFuncLJ1012Cut(v.structure,idx.data,prm.data,DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  copy(g,0.);
  BFuncLJ1012Cut(v.structure,idx.data,prm.data,DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

