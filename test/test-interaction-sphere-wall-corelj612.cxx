
#include "operation/interaction/spheric-shell-corelj612.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/geometry/distance-buffer-simple.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-spheric-shell-property.h"
#include "operation/parameter/build-param-ext-object-corelj612.h"
#include <iostream>
using namespace std;

int main() {

  DistanceBufferSimple<double>  DED;
  FreeSpace FS;
  allocate(DED,3,2);
  allocate(FS,3);

  PropertyList<double> v,g;
  Vector<unsigned int> sz(2);
  copy(sz,3);
  allocate(v,sz);
  allocate(g,sz);
  copy(v[0],1.);  v[0][1]=3.8;
  copy(v[1],0.);

  Vector<unsigned int> idx;
  allocate(idx,1);
  idx[0]=0;

  Vector<double> wv;
  Vector<UniqueParameter> prm,pprop;
  allocate(wv,3);
  allocate(prm,ExtObjCoreLJ612NumberParameter);
  allocate(pprop,SphericShellPropertyNumberParameter);
  prm[ExtObjectLocationPointer].ptr=reinterpret_cast<void*>(&wv);
  prm[ExtObjectPropertyPointer].ptr=reinterpret_cast<void*>(&pprop);
  prm[ExtObjCoreLJ612Radius].d=1.;
  prm[ExtObjCoreLJ612EnergyDepth].d=1.5;
  copy(wv,1.);
  pprop[SphericShellRadius].d=2.;
  pprop[SphericShellDirection].d=1.;
  BuildParameterExtObjCoreLJ612<double>(prm);
  BuildParameterSphericShellProperty<double>(pprop);

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncSphericShellCoreLJ612(v.structure,idx.data,prm.data,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  copy(g,0.);
  GFuncSphericShellCoreLJ612(v.structure,idx.data,prm.data,DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  copy(g,0.);
  BFuncSphericShellCoreLJ612(v.structure,idx.data,prm.data,DED,FS,
                             E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;
  return 0;
}

