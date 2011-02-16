
#include "operation/interaction/angle-harmonic.h"
#include "operation/geometry/distance-calc-simplebuffer.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "operation/parameter/build-param-angle-harmonic.h"
#include "operation/basic/property-list-io.h"
#include "data/basic/console-output.h"
using namespace std;

int main() {

  DistanceBufferSimple<double> DED;
  FreeSpace FS;
  allocate(DED,3,3);
  allocate(FS,3);
  
  PropertyList<double> v,g,tmv;
  Vector<unsigned int> sz;
  allocate(sz,4);
  copy(sz,3);
  allocate(v,sz);
  allocate(g,sz);
  allocate(tmv,sz);
  
  copy(v,0.);
  v[1][0]=1.2;
  v[2][0]=1.5;  v[2][1]=1.; v[2][2]=0.5;
  copy(g,0.);
  copy(tmv,0.);
  
  Vector<unsigned int> idx;
  allocate(idx,3);
  for(unsigned int i=0;i<3;++i) idx[i]=i;
  
  Vector<UniqueParameter> prm;
  allocate(prm,AngleHarmonicNumberParameter);
  prm[AngleHarmonicEqAngle].d=2./3.*M_PI;
  prm[AngleHarmonicEqStrength].d=20.;
  BuildParameterAngleHarmonic<double>(prm);
  
  double E;
  COut<<"Test -- calculate Energy of angle"<<Endl;
  E=0.;
  EFuncAngleHarmonic(v.structure,idx.data,prm.data,DED,FS,E);
  COut<<E<<Endl;
  COut<<Endl;

  COut<<"Test -- calculate Gradient of angle"<<Endl;
  copy(g,0.);
  GFuncAngleHarmonic(v.structure,idx(),prm(),DED,FS,g.structure,tmv.structure);
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- calculate Energy and Gradient of angle"<<Endl;
  E=0.;
  copy(g,0.);
  BFuncAngleHarmonic(v.structure,idx(),prm(),DED,FS,E,g.structure,
                     tmv.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  return 0;
}

