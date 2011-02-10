
#include "operation/interaction/anchor-point-harmonic.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/geometry/distance-buffer-simple.h"
#include "data/basic/property-list.h"
#include "operation/parameter/build-param-ext-object-harmonic.h"
#include "operation/basic/console-output.h"
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

  COut<<"Test -- EFunc"<<Endl;
  double E=0.;
  EFuncAnchorPointHarmonic(v.structure,idx.data,prm.data,DED,FS,E);
  COut<<E<<Endl;
  COut<<Endl;

  COut<<"Test -- GFunc"<<Endl;
  copy(g,0.);
  GFuncAnchorPointHarmonic(v.structure,idx.data,prm.data,DED,FS,g.structure);
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- BFunc"<<Endl;
  E=0.;
  copy(g,0.);
  BFuncAnchorPointHarmonic(v.structure,idx.data,prm.data,DED,FS,E,g.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  return 0;
}

