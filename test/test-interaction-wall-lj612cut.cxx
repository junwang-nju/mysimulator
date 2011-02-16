
#include "operation/interaction/plane-wall-lj612cut.h"
#include "operation/geometry/displacement-calc-freespace.h"
#include "data/geometry/distance-buffer-simple.h"
#include "operation/basic/property-list-io.h"
#include "operation/parameter/build-param-plane-wall-property.h"
#include "operation/parameter/build-param-ext-object-lj612cut.h"
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

  COut.precision(12);
  COut<<"\t"<<prm[ExtObjLJ612CutRealSigma6].d<<Endl;
  COut<<"\t"<<prm[ExtObjLJ612CutRealStrength].d<<Endl;
  COut<<"\t"<<prm[ExtObjLJ612CutVc].d<<Endl;
  COut<<"\t"<<prm[ExtObjLJ612CutKc].d<<Endl;

  COut<<"Test -- EFunc"<<Endl;
  double E=0.;
  EFuncPlaneWallLJ612Cut(v.structure,idx.data,prm.data,DED,FS,E);
  COut<<E<<Endl;
  COut<<Endl;

  COut<<"Test -- GFunc"<<Endl;
  copy(g,0.);
  GFuncPlaneWallLJ612Cut(v.structure,idx.data,prm.data,DED,FS,g.structure);
  COut<<g<<Endl;
  COut<<Endl;

  COut<<"Test -- BFunc"<<Endl;
  E=0.;
  copy(g,0.);
  BFuncPlaneWallLJ612Cut(v.structure,idx.data,prm.data,DED,FS,E,g.structure);
  COut<<E<<Endl;
  COut<<g<<Endl;
  COut<<Endl;

  return 0;
}

