
#include "operation/interaction/spheric-shell-lj612cut.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/geometry/distance-buffer-simple.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-spheric-shell-property.h"
#include "operation/parameter/build-param-ext-object-lj612cut.h"
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
  copy(v[0],1.);  v[0][0]=5;
  copy(v[1],0.);  v[1][0]=0.8;
  
  Vector<unsigned int> idx;
  allocate(idx,1);
  idx[0]=0;
  
  Vector<double> wv;
  Vector<UniqueParameter> prm,pprop;
  allocate(wv,3);
  allocate(prm,ExtObjLJ612CutNumberParameter);
  allocate(pprop,SphericShellPropertyNumberParameter);
  prm[ExtObjectLocationPointer].ptr=reinterpret_cast<void*>(&wv);
  prm[ExtObjectPropertyPointer].ptr=reinterpret_cast<void*>(&pprop);
  prm[ExtObjLJ612CutEqRadius].d=1.;
  prm[ExtObjLJ612CutEqEnergyDepth].d=1.5;
  prm[ExtObjLJ612CutCutR].d=2.5;
  copy(wv,1.);
  pprop[SphericShellRadius].d=2.;
  pprop[SphericShellDirection].d=1;
  BuildParameterExtObjLJ612Cut<double>(prm);
  BuildParameterSphericShellProperty<double>(pprop);

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncSphericShellLJ612Cut(v.structure,idx.data,prm.data,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  copy(g,0.);
  GFuncSphericShellLJ612Cut(v.structure,idx.data,prm.data,DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- EFunc"<<endl;
  E=0.;
  copy(g,0.);
  BFuncSphericShellLJ612Cut(v.structure,idx.data,prm.data,DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;
  return 0;
}
