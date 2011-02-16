
#include "operation/interaction/centroid-anchor-point-harmonic.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/geometry/distance-buffer-simple.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-ext-object-harmonic.h"
#include "data/basic/console-output.h"
#include "operation/basic/property-list-io.h"
using namespace std;

int main() {

  DistanceBufferSimple<double> DED;
  FreeSpace FS;
  allocate(DED,3,4);
  allocate(FS,3);

  PropertyList<double> v,g;
  Vector<unsigned int> sz;
  allocate(sz,4);
  copy(sz,2);
  allocate(v,sz);
  allocate(g,sz);
  copy(v[0],0.);
  copy(v[1],0.);  v[1][0]=1.3;
  copy(v[2],1.);
  copy(v[3],2.);  v[3][0]=0.3;
  
  Vector<unsigned int> idx;
  allocate(idx,6);
  idx[0]=2;
  idx[1]=4;
  for(unsigned int i=0;i<4;++i) idx[i+2]=i;
  
  Vector<double> wv;
  Vector<UniqueParameter> prm;
  allocate(wv,3);
  allocate(prm,ExtObjHarmonicNumberParameter);
  prm[ExtObjectLocationPointer].ptr=reinterpret_cast<void*>(&wv);
  copy(wv,-1.);
  prm[ExtObjHarmonicEqLength].d=2.;
  prm[ExtObjHarmonicEqStrength].d=100.;
  BuildParameterExtObjHarmonic<double>(prm);

  PropertyList<double> tmv;
  allocate(sz,1);
  copy(sz,3);
  allocate(tmv,sz);

  COut<<"Test -- EFunc"<<Endl;
  double E=0.;
  EFuncCentroidAnchorPointHarmonic(v.structure,idx.data,prm.data,DED,FS,
                                   E,tmv.structure);
  COut<<E<<Endl;
  COut<<Endl;

  COut<<"Test -- GFunc"<<Endl;
  copy(g,0.);
  GFuncCentroidAnchorPointHarmonic(v.structure,idx.data,prm.data,DED,FS,
                                   g.structure,tmv.structure);
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- BFunc"<<Endl;
  E=0.;
  copy(g,0.);
  BFuncCentroidAnchorPointHarmonic(v.structure,idx.data,prm.data,DED,FS,
                                   E,g.structure,tmv.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  return 0;
}
