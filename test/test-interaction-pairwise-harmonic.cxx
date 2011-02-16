
#include "operation/interaction/harmonic.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-harmonic.h"
#include "operation/basic/property-list-io.h"
#include "data/basic/console-output.h"
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
  COut<<v<<Endl;

  Vector<unsigned int> idx;
  allocate(idx,2);
  idx[0]=0;
  idx[1]=1;

  Vector<UniqueParameter> prm;
  allocate(prm,HarmonicNumberParameter);
  prm[HarmonicEqLength].d=1.;
  prm[HarmonicEqStrength].d=100.;
  BuildParameterHarmonic<double>(prm);

  COut<<"Test -- EFunc"<<Endl;
  double E=0.;
  EFuncHarmonic(v.structure,idx.data,prm.data,DED,FS,E);
  COut<<E<<Endl;
  COut<<Endl;

  COut<<"Test -- GFunc"<<Endl;
  copy(g,0.);
  GFuncHarmonic(v.structure,idx.data,prm.data,DED,FS,g.structure);
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- BFunc"<<Endl;
  E=0.;
  copy(g,0.);
  BFuncHarmonic(v.structure,idx.data,prm.data,DED,FS,E,g.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  return 1;
}

