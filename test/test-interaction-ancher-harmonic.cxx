
#include "operation/interaction/ancher-point-harmonic.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/geometry/distance-buffer-simple.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-ext-object-harmonic.h"
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
  copy(v[1],0.);  v[1][0]=0.8;

  Vector<unsigned int> idx;
  allocate(idx,1);
  idx[0]=0;

  Vector<double> wv;
  Vector<UniqueParameter> prm;
  allocate(wv,3);
  allocate(prm,ExtObjHarmonicNumberParameter);
  prm[ExtObjectLocationPointer].ptr=reinterpret_cast<void*>(&wv);
  copy(wv,1.);
  prm[ExtObjHarmonicEqLength].d=2.;
  prm[ExtObjHarmonicEqStrength].d=100.;
  BuildParameterExtObjHarmonic<double>(prm);

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncAncherPointHarmonic(v.structure,idx.data,prm.data,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  copy(g,0.);
  GFuncAncherPointHarmonic(v.structure,idx.data,prm.data,DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  copy(g,0.);
  BFuncAncherPointHarmonic(v.structure,idx.data,prm.data,DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

