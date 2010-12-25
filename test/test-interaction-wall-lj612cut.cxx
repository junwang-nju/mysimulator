
#include "operation/interaction/plane-wall-lj612cut.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-plane-wall-property.h"
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
  copy(v[0],0.);
  copy(v[1],0.);    v[1][0]=0.8;

  Vector<unsigned int> idx;
  allocate(idx,1);
  idx[0]=0;

  Vector<double> wv,wd;
  Vector<UniqueParameter> prm,pprop;
  allocate(wv,3);
  allocate(wd,3);
  allocate(prm,ExtObjLJ612CutNumberParameter);
  allocate(pprop,PlaneWallPropertyNumberParameter);
  prm[ExtObjectLocationPointer].ptr=reinterpret_cast<void*>(&wv);
  pprop[PlaneWallNormalDirectionPointer].ptr=reinterpret_cast<void*>(&wd);
  prm[ExtObjectPropertyPointer].ptr=reinterpret_cast<void*>(&pprop);
  prm[ExtObjLJ612CutEqRadius].d=1.;
  prm[ExtObjLJ612CutEqEnergyDepth].d=1.5;
  prm[ExtObjLJ612CutCutR].d=2.5;
  copy(wv,1.);
  wd[0]=1./sqrt(5);
  wd[1]=-2./sqrt(5);
  wd[2]=0.;
  BuildParameterExtObjLJ612Cut<double>(prm);
  BuildParameterPlaneWallProperty<double>(pprop);

  cout.precision(12);
  cout<<"\t"<<prm[ExtObjLJ612CutRealSigma6].d<<endl;
  cout<<"\t"<<prm[ExtObjLJ612CutRealStrength].d<<endl;
  cout<<"\t"<<prm[ExtObjLJ612CutVc].d<<endl;
  cout<<"\t"<<prm[ExtObjLJ612CutKc].d<<endl;

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncPlaneWallLJ612Cut(v.structure,idx.data,prm.data,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  copy(g,0.);
  GFuncPlaneWallLJ612Cut(v.structure,idx.data,prm.data,DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  copy(g,0.);
  BFuncPlaneWallLJ612Cut(v.structure,idx.data,prm.data,DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

