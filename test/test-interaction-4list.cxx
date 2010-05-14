
#include "interaction-4list.h"
#include "property-list.h"
#include "interaction-method.h"
#include "distance-evaluate-direct.h"
#include "free-space.h"
#include "parameter-list.h"
#include <iostream>
using namespace std;

int main() {

  unsigned int *sz;

  PropertyList<double> Coor,Grad;
  sz=new unsigned int[4];
  assign(sz,2,4);
  allocate(Coor,sz,4);
  allocate(Grad,sz,4);
  Coor[0][0]=0;       Coor[0][1]=0;
  Coor[1][0]=0;       Coor[1][1]=1.2;
  Coor[2][0]=1.3;     Coor[2][1]=1.5;
  Coor[3][0]=0.8;     Coor[3][1]=2.2;
  safe_delete_array(sz);

  PropertyList<unsigned int> IdxLst;
  sz=new unsigned int[6];
  assign(sz,2,6);
  allocate(IdxLst,sz,6);
  IdxLst[0][0]=0;     IdxLst[0][1]=1;
  IdxLst[1][0]=0;     IdxLst[1][1]=2;
  IdxLst[2][0]=0;     IdxLst[2][1]=3;
  IdxLst[3][0]=1;     IdxLst[3][1]=2;
  IdxLst[4][0]=1;     IdxLst[4][1]=3;
  IdxLst[5][0]=2;     IdxLst[5][1]=3;
  safe_delete_array(sz);

  Vector<unsigned int> Kind;
  allocate(Kind,4);
  Kind[0]=0;
  Kind[1]=1;
  Kind[2]=0;
  Kind[3]=2;
  ParameterList PL;
  allocate(PL,3,HarmonicNumberParameter,9);
  for(unsigned int i=0,n=0;i<3;++i)
  for(unsigned int j=0;j<3;++j,++n) {
    PL.key[n].index[0]=PairwiseHarmonic;
    PL.key[n].index[1]=i;
    PL.key[n].index[2]=j;
    buildhash(PL.key[n]);
  }
  PL.value[0][HarmonicEqLength]=1.;
  PL.value[0][HarmonicEqStrength]=100.;
  PL.value[1][HarmonicEqLength]=2.;
  PL.value[1][HarmonicEqStrength]=100.;
  PL.value[2][HarmonicEqLength]=0.5;
  PL.value[2][HarmonicEqStrength]=100.;
  PL.value[3]=PL.value[1];
  PL.value[4][HarmonicEqLength]=1.;
  PL.value[4][HarmonicEqStrength]=200.;
  PL.value[5][HarmonicEqLength]=1.;
  PL.value[5][HarmonicEqStrength]=30.;
  PL.value[6]=PL.value[2];
  PL.value[7]=PL.value[5];
  PL.value[8][HarmonicEqLength]=1.5;
  PL.value[8][HarmonicEqStrength]=2000.;
  for(unsigned int n=0;n<9;++n)
    GenerateParameterHarmonic(PL.value[n]);
  updatetree(PL);
  Vector<UniqueParameter>* Prm=new Vector<UniqueParameter>[6];
  Vector<unsigned int> pKey;
  allocate(pKey,3);
  for(unsigned int i=0;i<6;++i) {
    pKey[0]=PairwiseHarmonic;
    pKey[1]=Kind[IdxLst[i][0]];
    pKey[2]=Kind[IdxLst[i][1]];
    refer(Prm[i],*get(PL,pKey(),3));
  }
  release(pKey);

  InteractionMethod<DistanceEvalDirect,FreeSpace> IM;
  allocate(IM);
  Set(IM,PairwiseHarmonic);

  DistanceEvalDirect DEval;
  FreeSpace FS;
  allocate(DEval,2,4);
  allocate(FS,2);

  cout<<"Test -- EFunc"<<endl;
  double E;
  E=0.;
  EFunc(Coor.structure,IdxLst.structure,Prm,6,IM,DEval,FS,E);
  cout<<E<<endl;
  cout<<endl;
  
  cout<<"Test -- GFunc"<<endl;
  assign(Grad.data,0.,Grad.size);
  GFunc(Coor.structure,IdxLst.structure,Prm,6,IM,DEval,FS,Grad.structure);
  cout<<Grad<<endl;
  cout<<endl;
  
  cout<<"Test -- BFunc"<<endl;
  E=0.;
  assign(Grad.data,0.,Grad.size);
  BFunc(Coor.structure,IdxLst.structure,Prm,6,IM,DEval,FS,E,Grad.structure);
  cout<<E<<endl;
  cout<<Grad<<endl;
  cout<<endl;
  
  return 1;
}

