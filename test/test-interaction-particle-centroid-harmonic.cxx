
#include "operation/interaction/particle-centroid-harmonic.h"
#include "data/geometry/distance-buffer-simple.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-harmonic.h"
#include <iostream>
using namespace std;

int main() {

  DistanceBufferSimple<double> DED;
  FreeSpace FS;
  allocate(DED,3,2);
  allocate(FS,3);

  PropertyList<double> v,g;
  Vector<unsigned int> sz(5);
  copy(sz,2);
  allocate(v,sz);
  allocate(g,sz);
  copy(v[0],0.);
  copy(v[1],0.);    v[1][0]=1.3;
  copy(v[2],1.);
  copy(v[3],2.);    v[3][0]=0.3;
  copy(v[4],0.5);   v[4][0]=-1.7;

  Vector<unsigned int> idx;
  allocate(idx,7);
  idx[0]=0;
  idx[1]=1+2;
  idx[2]=4;
  for(unsigned int i=1;i<5;++i) idx[i+2]=i;

  Vector<UniqueParameter> prm;
  allocate(prm,HarmonicNumberParameter);
  prm[HarmonicEqLength].d=1.;
  prm[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(prm);

  PropertyList<double> tmv;
  allocate(sz,2);
  copy(sz,2);
  allocate(tmv,sz);

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncParticleCentroidHarmonic(v.structure,idx.data,prm.data,DED,FS,
                                E,tmv.structure);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  copy(g,0.);
  GFuncParticleCentroidHarmonic(v.structure,idx.data,prm.data,DED,FS,
                                g.structure,tmv.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  copy(g,0.);
  BFuncParticleCentroidHarmonic(v.structure,idx.data,prm.data,DED,FS,
                                E,g.structure,tmv.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

