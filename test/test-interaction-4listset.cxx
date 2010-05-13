
#include "interaction-4listset.h"
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
  PropertyList<Vector<unsigned int> > IdxSet;
  sz=new unsigned int[2];
  assign(sz,3,2);
  allocate(IdxSet,sz,2);
  for(unsigned int i=0,n=0;i<2;++i)
  for(unsigned int j=0;j<3;++j,++n)
    refer(IdxSet[i][j],IdxLst[n]);
  safe_delete_array(sz);

  Vector<unsigned int> Kind;
  allocate(Kind,4);
  Kind[0]=0;
  Kind[1]=1;
  Kind[2]=0;
  Kind[3]=2;
  ParameterList PL;
  sz=new unsigned int[18];
  for(unsigned int i=0;i<9;++i)   sz[i]=HarmonicNumberParameter;
  for(unsigned int i=9;i<18;++i)  sz[i]=LJ612NumberParameter;
  allocate(PL,3,sz,18);
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
  for(unsigned int i=0,n=9;i<3;++i)
  for(unsigned int j=0;j<3;++j,++n) {
    PL.key[n].index[0]=PairwiseLJ612;
    PL.key[n].index[1]=i;
    PL.key[n].index[2]=j;
    buildhash(PL.key[n]);
  }
  PL.value[9][LJ612EqRadius]=1.;
  PL.value[9][LJ612EqEnergyDepth]=1.;
  PL.value[10][LJ612EqRadius]=0.8;
  PL.value[10][LJ612EqEnergyDepth]=2.;
  PL.value[11][LJ612EqRadius]=0.5;
  PL.value[11][LJ612EqEnergyDepth]=1.;
  PL.value[12]=PL.value[10];
  PL.value[13][LJ612EqRadius]=1.2;
  PL.value[13][LJ612EqEnergyDepth]=2.;
  PL.value[14][LJ612EqRadius]=1.1;
  PL.value[14][LJ612EqEnergyDepth]=3.;
  PL.value[15]=PL.value[11];
  PL.value[16]=PL.value[14];
  PL.value[17][LJ612EqRadius]=1.5;
  PL.value[17][LJ612EqEnergyDepth]=2.;
  for(unsigned int n=9;n<18;++n)
    GenerateParameterLJ612(PL.value[n]);
  updatetree(PL);
  Vector<UniqueParameter>* Prm=new Vector<UniqueParameter>[6];
  Vector<unsigned int> pKey;
  allocate(pKey,3);
  for(unsigned int i=0;i<3;++i) {
    pKey[0]=PairwiseHarmonic;
    pKey[1]=Kind[IdxLst[i][0]];
    pKey[2]=Kind[IdxLst[i][1]];
    refer(Prm[i],*get(PL,pKey(),3));
  }
  for(unsigned int i=3;i<6;++i) {
    pKey[0]=PairwiseLJ612;
    pKey[1]=Kind[IdxLst[i][0]];
    pKey[2]=Kind[IdxLst[i][1]];
    refer(Prm[i],*get(PL,pKey(),3));
  }
  release(pKey);
  PropertyList<Vector<UniqueParameter> > PrmSet;
  sz=new unsigned int[2];
  assign(sz,3,2);
  allocate(PrmSet,sz,2);
  for(unsigned int i=0,n=0;i<2;++i)
  for(unsigned int j=0;j<3;++j,++n)
    refer(PrmSet[i][j],Prm[n]);
  safe_delete_array(sz);

  InteractionMethod<DistanceEvalDirect,FreeSpace>* IM;
  IM=new InteractionMethod<DistanceEvalDirect,FreeSpace>[2];
  for(unsigned int i=0;i<2;++i)   allocate(IM[i]);
  Set(IM[0],PairwiseHarmonic);
  Set(IM[1],PairwiseLJ612);

  DistanceEvalDirect DEval;
  FreeSpace FS;
  allocate(DEval,2);
  allocate(FS,2);

  cout.precision(20);
  cout<<"Test -- EFunc"<<endl;
  double E;
  E=0.;
  EFunc(Coor.structure,IdxSet.structure,PrmSet.structure,IM,2,DEval,FS,E);
  cout<<E<<endl;
  cout<<endl;
  
  cout<<"Test -- GFunc"<<endl;
  assign(Grad.data,0.,Grad.size);
  GFunc(Coor.structure,IdxSet.structure,PrmSet.structure,IM,2,DEval,FS,
        Grad.structure);
  cout<<Grad<<endl;
  cout<<endl;
  
  cout<<"Test -- BFunc"<<endl;
  E=0.;
  assign(Grad.data,0.,Grad.size);
  BFunc(Coor.structure,IdxSet.structure,PrmSet.structure,IM,2,DEval,FS,
        E,Grad.structure);
  cout<<E<<endl;
  cout<<Grad<<endl;
  cout<<endl;

  safe_delete_array(IM);
  IM=new InteractionMethod<DistanceEvalDirect,FreeSpace>[6];
  for(unsigned int i=0;i<6;++i) allocate(IM[i]);
  for(unsigned int i=0;i<3;++i) Set(IM[i],PairwiseHarmonic);
  for(unsigned int i=3;i<6;++i) Set(IM[i],PairwiseLJ612);

  cout<<"Test -- EFunc (series version)"<<endl;
  E=0.;
  EFunc(Coor.structure,IdxLst.structure,Prm,IM,6,DEval,FS,E);
  cout<<E<<endl;
  cout<<endl;
  
  cout<<"Test -- GFunc"<<endl;
  assign(Grad.data,0.,Grad.size);
  GFunc(Coor.structure,IdxLst.structure,Prm,IM,6,DEval,FS,Grad.structure);
  cout<<Grad<<endl;
  cout<<endl;
  
  cout<<"Test -- BFunc"<<endl;
  E=0.;
  assign(Grad.data,0.,Grad.size);
  BFunc(Coor.structure,IdxLst.structure,Prm,IM,6,DEval,FS,E,Grad.structure);
  cout<<E<<endl;
  cout<<Grad<<endl;
  cout<<endl;

  safe_delete_array(IM);
  
  return 1;
}

