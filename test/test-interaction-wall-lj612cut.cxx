
#include "interaction-wall-lj612cut.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include "property-list.h"
#include <iostream>
using namespace std;

int main() {

  DistanceEvalDirect DED;
  FreeSpace FS;
  allocate(DED,3,2);
  allocate(FS,3);

  PropertyList<double> v,g;
  unsigned int *sz=new unsigned int[2];
  assign(sz,3,2);
  allocate(v,sz,2);
  allocate(g,sz,2);
  assign(v[0],0.);
  assign(v[1],0.);    v[1][0]=0.8;

  Vector<unsigned int> idx;
  allocate(idx,1);
  idx[0]=0;

  Vector<UniqueParameter> prm;
  allocateWallLJ612CutParameter(prm,PlaneWallType,3);
  prm[WallLJ612CutEqRadius]=1.;
  prm[WallLJ612CutEqEnergyDepth]=1.5;
  prm[WallLJ612CutCutR]=2.5;
  prm[prm[WallShapeParameterShift].u+0]=1.;
  prm[prm[WallShapeParameterShift].u+1]=1.;
  prm[prm[WallShapeParameterShift].u+2]=1.;
  prm[prm[WallShapeParameterShift].u+3]=1./sqrt(5);
  prm[prm[WallShapeParameterShift].u+4]=-2./sqrt(5);
  prm[prm[WallShapeParameterShift].u+5]=0.;
  GenerateParameterWallLJ612Cut(prm,DED,FS);

  cout.precision(12);
  cout<<"\t"<<prm[WallLJ612CutRealSigma6].d<<endl;
  cout<<"\t"<<prm[WallLJ612CutRealStrength].d<<endl;
  cout<<"\t"<<prm[WallLJ612CutVc].d<<endl;
  cout<<"\t"<<prm[WallLJ612CutKc].d<<endl;

  cout<<"Test -- EFunc"<<endl;
  double E=0.;
  EFuncWallLJ612Cut(v.structure,idx(),prm(),1,NULL,0,DED,FS,E);
  cout<<E<<endl;
  cout<<endl;

  cout<<"Test -- GFunc"<<endl;
  assign(g.data,0.,g.size);
  GFuncWallLJ612Cut(v.structure,idx(),prm(),1,NULL,0,DED,FS,g.structure);
  cout<<g<<endl;
  cout<<endl;

  cout<<"Test -- BFunc"<<endl;
  E=0.;
  assign(g.data,0.,g.size);
  BFuncWallLJ612Cut(v.structure,idx(),prm(),2,NULL,0,DED,FS,E,g.structure);
  cout<<E<<endl;
  cout<<g<<endl;
  cout<<endl;

  return 0;
}

