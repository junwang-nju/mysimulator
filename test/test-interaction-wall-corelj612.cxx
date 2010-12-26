
#include "operation/interaction/plane-wall-corelj612.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/geometry/distance-buffer-simple.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-plane-wall-property.h"
#include "operation/parameter/build-param-ext-object-corelj612.h"
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
  copy(v[1],0.);    v[1][0]=0.8;

  Vector<unsigned int> idx;
  allocate(idx,1);
  idx[0]=0;

  Vector<double> wv,wd;
  Vector<UniqueParameter> prm,pprop;
  allocate(wv,3);
  allocate(wd,3);
  allocate(prm,ExtObjCoreLJ612NumberParameter);
  allocate(pprop,PlaneWallPropertyNumberParameter);
  prm[ExtObjectLocationPointer].ptr=reinterpret_cast<void*>(&wv);
  pprop[PlaneWallNormalDirectionPointer].ptr=reinterpret_cast<void*>(&wd);
  prm[ExtObjectPropertyPointer].ptr=reinterpret_cast<void*>(&pprop);
  prm[ExtObjCoreLJ612Radius].d=1.;
  prm[ExtObjCoreLJ612EnergyDepth].d=1.5;
  copy(wv,1.);
  wd[0]=1./sqrt(5);
  wd[1]=-2./sqrt(5);
  wd[2]=0.;
  BuildParameterExtObjCoreLJ612<double>(prm);
  BuildParameterPlaneWallProperty<double>(pprop);

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncPlaneWallCoreLJ612(v.structure,idx.data,prm.data,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  copy(g,0.);
  GFuncPlaneWallCoreLJ612(v.structure,idx.data,prm.data,DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  copy(g,0.);
  BFuncPlaneWallCoreLJ612(v.structure,idx.data,prm.data,DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

