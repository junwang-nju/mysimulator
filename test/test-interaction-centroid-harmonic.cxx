
#include "operation/interaction/centroid-centroid-harmonic.h"
#include "data/geometry/distance-buffer-simple.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/basic/console-output.h"
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
  allocate(idx,9);
  idx[0]=3;
  idx[1]=2;
  idx[2]=3;
  for(unsigned int i=0;i<5;++i) idx[i+3]=i;

  Vector<UniqueParameter> prm;
  allocate(prm,HarmonicNumberParameter);
  prm[HarmonicEqLength].d=1.;
  prm[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(prm);

  PropertyList<double> tmv;
  allocate(sz,2);
  copy(sz,2);
  allocate(tmv,sz);

  COut<<"Test -- EFunc"<<Endl;
  double E=0.;
  EFuncCentroidCentroidHarmonic(v.structure,idx.data,prm.data,DED,FS,
                                E,tmv.structure);
  COut<<E<<Endl;
  COut<<Endl;

  COut<<"Test -- GFunc"<<Endl;
  copy(g,0.);
  GFuncCentroidCentroidHarmonic(v.structure,idx.data,prm.data,DED,FS,
                                g.structure,tmv.structure);
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- BFunc"<<Endl;
  E=0.;
  copy(g,0.);
  BFuncCentroidCentroidHarmonic(v.structure,idx.data,prm.data,DED,FS,
                                E,g.structure,tmv.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  return 0;
}

